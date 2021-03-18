/*
 * Project: p2
 * File: p2/main.cpp
 * -----
 * File Created: Wednesday, 10th February 2021 7:34:47 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:30:17 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <iostream>
#include <array>

inline constexpr bool AND(bool a, bool b) noexcept
{
    return a & b;
}

inline constexpr bool OR(bool a, bool b) noexcept
{
    return a | b;
}

inline constexpr bool XOR(bool a, bool b) noexcept
{
    return a ^ b;
}

inline constexpr std::array<bool, 2> half_adder(bool a, bool b) noexcept
{
    return {XOR(a, b), AND(a, b)};
}

inline constexpr std::array<bool, 2> full_adder(bool a, bool b, bool ci) noexcept
{
    const std::array<bool, 2> ha_1 = half_adder(a, b);
    const std::array<bool, 2> ha_2 = half_adder(ha_1[0], ci);
    return {ha_2[0], OR(ha_1[1], ha_2[1])};
}

template<int SIZE>
std::array<bool, SIZE> bit_adder(std::array<bool, SIZE> a, std::array<bool, SIZE> b, bool& carry, bool& overflow) noexcept
{
    std::array<bool, SIZE> s;
    for (int i = 0; i < SIZE; ++i)
    {
        std::array<bool, 2> res = full_adder(a[i], b[i], carry);
        s[i] = res[0];
        carry = res[1];
        if (i < SIZE - 2)
        {
            overflow = carry;
        }
    }
    return s;
}

std::ostream& operator<< (std::ostream& os, const std::array<bool, 8>& arr)
{
    for (std::array<bool, 8>::const_iterator it = arr.end() - 1; it >= arr.begin(); --it)
    {
        os << *it;
    }
    return os;
}

std::array<bool, 4> create_bit_array(int8_t num) noexcept
{
    std::array<bool, 4> out = {0,0,0,0};
    int i = 0;
    for (int i = 0; i < 4; ++i)
    {
        out[i] = num & 0b1;
        num >>= 1;
    }
    return out;
}

int8_t bit_array_to_num(std::array<bool, 8> arr) noexcept
{
    int8_t num = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        num |= arr[i] << i;
    }
    return num;
}

void invert(std::array<bool, 8>& arr)
{
    for (bool& val : arr)
    {
        val = !val;
    }
}

std::array<bool, 4> get_prod(std::array<bool, 4> arr, bool b)
{
    std::array<bool, 4> out;
    for (int i = 0; i < 4; ++i)
    {
        out[i] = arr[i] & b;
    }
    return out;
}

std::array<bool, 4> shift(std::array<bool, 4> arr)
{
    std::array<bool, 4> out;
    for (int i = arr.size() - 1; i > 0; --i)
    {
        out[i-1] = arr[i];
    }
    return out;
}

std::array<bool, 8> mult_4(std::array<bool, 4> a, std::array<bool, 4> b)
{
    bool carry=false,overflow;
    std::array<bool, 8> res;
    std::array<bool, 4> acc = get_prod(a, b[0]);
    res[0] = acc[0];
    for (int i = 1; i < 4; ++i)
    {
        acc = shift(acc);
        acc[3] = carry;
        std::array<bool, 4> prod = get_prod(a, b[i]);
        bool carry=false;
        acc = bit_adder<4>(acc, prod, carry, overflow);
        res[i] = acc[0];
    }
    for (int i = 0 ; i < 4; ++i)
    {
        res[i + 3] = acc[i];
    }
    res[7] = carry;
    return res;
}

int main(int argc, char** argv)
{
    int a, b;
    std::cout << "Input your first number (A): ";
    std::cin >> a;
    std::cout << "Input your first number (B): ";
    std::cin >> b;

    std::array<bool, 4> a_bits = create_bit_array(a);
    std::array<bool, 4> b_bits = create_bit_array(b);

    std::array<bool, 8> res = mult_4(a_bits, b_bits);

    int num = bit_array_to_num(res);

    std::cout << "Binary: " << res << std::endl;
    std::cout << "Decimal Equivalent: " << num << std::endl;

    return 0;
}