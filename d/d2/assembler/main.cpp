#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <stdexcept>

std::string load_file(const std::string& filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::string remove_comments(const std::string& str)
{
    std::string uncommented;
    for (const char& c : str)
    {
        if (c == ';')
        {
            return uncommented;
        }
        uncommented += c;
    }
    return uncommented;
}

std::string remove_extra_whitespace(const std::string& str)
{
    std::string whitespace_compressed;
    bool prev_char_whitespace = true;
    for (const char& c : str)
    {
        if (c == ' ' || c == '\t')
        {
            if (!prev_char_whitespace)
            {
                whitespace_compressed += c;
            }
            prev_char_whitespace = true;
        }
        else
        {
            prev_char_whitespace = false;
            whitespace_compressed += c;
        }
    }
    if (whitespace_compressed.back() == ' ' || whitespace_compressed.back() == '\t')
    {
        whitespace_compressed.pop_back();
    }
    return whitespace_compressed;
}

std::vector<std::string> compress_labels(std::vector<std::string> lines)
{
    std::vector<std::string> compressed;
    std::string from_last;
    for (const std::string& str : lines)
    {
        if (str.find(':') != std::string::npos)
        {
            if (std::find(str.begin(), str.end(), ':') == str.end() - 1)
            {
                from_last += str;
                continue;
            }
        }
        compressed.push_back(from_last + str);
        from_last = "";
    }
    return compressed;
}

std::vector<std::string> preprocess(const std::string& raw)
{
    std::vector<std::string> preprocessed;
    std::istringstream ss(raw);
    std::string line;
    while (std::getline(ss, line, '\n'))
    {
        line = remove_comments(line);
        line = remove_extra_whitespace(line);
        if (!line.empty())
        {
            preprocessed.push_back(line);
        }
    }
    return compress_labels(preprocessed);
}

std::pair<std::string, std::string> parse_line(const std::string& str, char delim)
{
    if (str.find(delim) == std::string::npos)
    {
        throw std::runtime_error("only one token on line: " + str);
    }
    if (std::count(str.begin(), str.end(), ' ') > 2)
    {
        throw std::runtime_error("too many tokens on line: " + str);
    }
    std::pair<std::string, std::string> split;
    split.first = str.substr(0, str.find(' '));
    split.second = str.substr(str.find(' ') + 1, str.length() - str.find(' '));
    return split;
}

std::vector<std::pair<std::string, std::string>> tokenise(const std::vector<std::string>& lines)
{
    std::vector<std::string> new_lines;
    std::unordered_map<std::string, int> label_map;
    for (int i = 0; i < lines.size(); ++i)
    {
        int j = 0;
        if (lines[i].find(':') != std::string::npos)
        {
            std::string identifier;
            for (; j < lines[i].size(); ++j)
            {
                if (lines[i][j] != ':')
                {
                    identifier += lines[i][j];
                }
                else
                {
                    ++j;
                    break;
                }
            }
            if (!identifier.empty())
            {
                label_map.insert(std::make_pair(identifier, i));
            }
        }
        std::string new_line;
        for (; j < lines[i].size(); ++j)
        {
            new_line += lines[i][j];
        }
        new_lines.push_back(new_line);
    }
    
    std::vector<std::pair<std::string, std::string>> parsed_lines;
    for (const std::string& str : new_lines)
    {
        parsed_lines.push_back(parse_line(str, ' '));
    }
    for (std::pair<std::string, std::string>& parsed_line : parsed_lines)
    {
        if (label_map.find(parsed_line.second) != label_map.end())
        {
            parsed_line.second = std::to_string(label_map[parsed_line.second]);
        }
    }
    return parsed_lines;
}

bool is_str_int(const std::string str)
{
    for (const char& c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

uint8_t calc_machine_code(const std::pair<std::string, std::string>& instr, int prog_len, std::vector<int>& constants)
{
    const static std::unordered_map<std::string, uint8_t> opcodes = {
        std::make_pair("ldr", 0),
        std::make_pair("str", 1),
        std::make_pair("add", 2),
        std::make_pair("sub", 3),
        std::make_pair("bne", 4),
        std::make_pair("xor", 5),
        std::make_pair("drf", 6),
    };
    if (opcodes.find(instr.first) == opcodes.end())
    {
        throw std::runtime_error("invalid opcode " + instr.first);
    }
    uint8_t opcode = opcodes.at(instr.first);
    uint8_t address;
    if (opcode == 0b110) return opcode << 5;
    if (instr.second[0] == '[' && instr.second.back() == ']')
    {
        if (!is_str_int(instr.second.substr(1, instr.second.length() - 2)))
        {
            throw std::runtime_error("not a valid operand: " + instr.second);
        }
        address = stoi(instr.second.substr(1, instr.second.length() - 2));
    }
    else
    {
        if (!is_str_int(instr.second))
        {
            throw std::runtime_error("not a valid operand: " + instr.second);
        }
        address = prog_len + constants.size();
        constants.push_back(stoi(instr.second));
    }
    return (opcode << 5) | address;
}

std::vector<uint8_t> compile(const std::vector<std::pair<std::string, std::string>>& lines)
{
    std::vector<int> constants;
    std::vector<uint8_t> machine_code;
    for (const std::pair<std::string, std::string>& line : lines)
    {
        machine_code.push_back(calc_machine_code(line, lines.size(), constants));
    }
    for (int& constant : constants)
    {
        machine_code.push_back(constant);
    }
    return machine_code;
}

std::string conv_to_sv(const std::vector<uint8_t>& machine_code)
{
    std::string sv_code;
    for (int i = 0; i < machine_code.size(); ++i)
    {
        std::string line = std::to_string(i) + ": mdr = {`";
        switch ((machine_code[i] >> 5) & 0b111)
        {
        case 0:
            line += "LOAD, 5'd";
            break;
        case 1:
            line += "STORE, 5'd";
            break;
        case 2:
            line += "ADD, 5'd";
            break;
        case 3:
            line += "SUB, 5'd";
            break;
        case 4:
            line += "BNE, 5'd";
            break;
        case 5:
            line += "XOR, 5'd";
            break;
        case 6:
            line += "DEREF, 5'd";
            break;
        }
        sv_code += line + std::to_string(machine_code[i] & 0b11111) + "};\n";
    }
    sv_code.pop_back();
    return sv_code;
}

void output_string_to_file(const std::string& str, const std::string& filename)
{
    std::ofstream out_file(filename);
    out_file << str << std::endl;
    out_file.close();
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: not enough arguments, usage: " << argv[0] << " [input filename] [output filename]\n";
        return 1;
    }
    try
    {
        std::string raw_file = load_file(argv[1]);
        std::vector<std::string> preprocesssed_file = preprocess(raw_file);
        std::vector<std::pair<std::string, std::string>> tokenised = tokenise(preprocesssed_file);
        std::vector<uint8_t> machine_code = compile(tokenised);
        std::string sv_code = conv_to_sv(machine_code);
        output_string_to_file(sv_code, argv[2]);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}