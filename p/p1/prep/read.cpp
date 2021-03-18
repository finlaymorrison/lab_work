/*
 * Project: prep
 * File: prep/read.cpp
 * -----
 * File Created: Monday, 1st February 2021 9:34:40 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:29:48 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <fstream>
#include <iostream>
#include <vector>

template<typename TYPE>
std::ostream& operator<< (std::ostream& os, std::vector<TYPE> vec)
{
    os << '{';
    for (int i = 0; i < vec.size() - 1; ++i)
    {
        os << vec[i] << ',';
    }
    return os << vec.back() << '}';

}

int main(int argc, char** argv)
{
    std::vector<char> chars;
    std::ifstream file("input-data.txt");
    char c;
    while (file >> c)
    {
        chars.push_back(c);
    }
    file.close();
    std::cout << chars << std::endl;
    return 0;
}