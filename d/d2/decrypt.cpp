#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

std::vector<char> table = {'@', 'a', 'b', 'c', 'd','e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '/', ']', '.'};

class mapped_string
{
private:
    std::string raw;
public:
    mapped_string(std::string str) :
        raw(str.size(), '0')
    {
        std::transform(str.begin(), str.end(), raw.begin(), [](char c){
            return std::distance(table.begin(), std::find(table.begin(), table.end(), c));
        });
    }
    mapped_string() = default;
    std::string::iterator begin()
    {
        return raw.begin();
    }
    std::string::iterator end()
    {
        return raw.end();
    }
    mapped_string& operator+= (char c)
    {
        raw += c;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, mapped_string str)
{
    for (char c : str)
    {
        os << table[c];
    }
    return os;
}

int main(int argc, char** argv)
{
    mapped_string str("oiytmmvk");
    for (uint8_t key = 0; key < 32; ++key)
    {
        mapped_string decrypted;
        for (char c : str)
        {
            decrypted += c ^ key;
        }
        std::cout << static_cast<int>(key) << ':' << decrypted << std::endl;
    }
}