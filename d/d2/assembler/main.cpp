#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <bitset>

std::string load_file(std::string filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::string remove_comments(std::string str)
{
    std::string uncommented;
    for (char c : str)
    {
        if (c == ';')
        {
            return uncommented;
        }
        uncommented += c;
    }
    return uncommented;
}

std::string remove_extra_whitespace(std::string str)
{
    std::string whitespace_compressed;
    bool prev_char_whitespace = true;
    for (char c : str)
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
    for (std::string str : lines)
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

std::vector<std::string> preprocess(std::string raw)
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

std::vector<std::string> split_string(std::string str, char delim)
{
    std::vector<std::string> split_strings;
    std::string curr_part;
    for (char c : str)
    {
        if (c == delim)
        {
            split_strings.push_back(curr_part);
            curr_part = "";
            continue;
        }
        else
        {
            curr_part += c;
        }
    }
    split_strings.push_back(curr_part);
    return split_strings;
}

std::vector<std::vector<std::string>> split_lines_and_sub(std::vector<std::string> lines)
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
    
    std::vector<std::vector<std::string>> split_lines;
    for (std::string str : new_lines)
    {
        split_lines.push_back(split_string(str, ' '));
    }
    for (std::vector<std::string>& strs : split_lines)
    {
        for (std::string& str : strs)
        {
            if (label_map.find(str) != label_map.end())
            {
                str = std::to_string(label_map[str]);
            }
        }
    }
    return split_lines;
}

uint8_t calc_machine_code(std::vector<std::string> instr, int prog_len, std::vector<int>& constants)
{
    std::unordered_map<std::string, uint8_t> opcodes = {
        std::make_pair("ldr", 0),
        std::make_pair("str", 1),
        std::make_pair("add", 2),
        std::make_pair("sub", 3),
        std::make_pair("bne", 4),
        std::make_pair("xor", 5),
        std::make_pair("drf", 6),
    };
    uint8_t opcode = opcodes[instr[0]];
    uint8_t address;
    if (opcode == 0b110) return opcode << 5;
    if (instr.back()[0] == '[')
    {
        address = stoi(instr.back().substr(1, instr.back().length() - 2));
    }
    else
    {
        address = prog_len + constants.size();
        constants.push_back(stoi(instr.back()));
    }
    return (opcode << 5) | address;
}

std::vector<uint8_t> compile(std::vector<std::vector<std::string>> lines)
{
    std::vector<int> constants;
    std::vector<uint8_t> machine_code;
    for (std::vector<std::string> line : lines)
    {
        machine_code.push_back(calc_machine_code(line, lines.size(), constants));
    }
    for (int constant : constants)
    {
        machine_code.push_back(constant);
    }
    return machine_code;
}

std::string conv_to_sv(std::vector<uint8_t> machine_code)
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
        line += std::to_string(machine_code[i] & 0b11111) + "};";
        sv_code += line + '\n';
    }
    sv_code.pop_back();
    return sv_code;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Error: not enough arguments, usage: " << argv[0] << " [input filename] [output filename]\n";
        return 1;
    }
    std::string raw_file = load_file(argv[1]);
    std::vector<std::string> preprocesssed_file = preprocess(raw_file);
    std::vector<std::vector<std::string>> shredded = split_lines_and_sub(preprocesssed_file);
    std::vector<uint8_t> machine_code = compile(shredded);
    std::string sv_code = conv_to_sv(machine_code);
    std::ofstream out_file(argv[2]);
    out_file << sv_code << std::endl;
    out_file.close();
    return 0;
}