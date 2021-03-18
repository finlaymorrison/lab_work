/*
 * Project: p2
 * File: p2/prep.cpp
 * -----
 * File Created: Friday, 5th February 2021 1:54:18 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:30:15 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <iostream>
#include <utility>
#include <functional>
#include <type_traits>
#include <tuple>
#include <cmath>
#include <sstream>
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
    std::array<bool, 2> ha_1 = half_adder(a, b);
    std::array<bool, 2> ha_2 = half_adder(ha_1[0], ci);
    return {ha_2[0], OR(ha_1[1], ha_2[1])};
}

template<int SIZE>
std::array<bool, SIZE> bit_adder(std::array<bool, SIZE> a, std::array<bool, SIZE> b) noexcept
{
    std::array<bool, SIZE> s;
    bool carry = false;
    for (int i = 0; i < SIZE; ++i)
    {
        std::array<bool, 2> res = full_adder(a[i], b[i], carry);
        s[i] = res[0];
        carry = res[1];
    }
    return s;
}

std::array<bool, 8> create_bit_array(int8_t num) noexcept
{
    std::array<bool, 8> out;
    int i = 0;
    do
    {
        out[i++] = num & 0b1;
    }
    while (num >>= 1);
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

int8_t bit_adder(int8_t a, int8_t b) noexcept
{
    std::array<bool, 8> res = bit_adder<8>(create_bit_array(a), create_bit_array(b));
    return bit_array_to_num(res);
}

template<
    size_t INDEX,
    typename... ELEMS,
    typename std::enable_if<std::is_same<bool, typename std::common_type<ELEMS...>::type>::value, int>::type = 0
>
void inc_tuple_bin_seq(std::tuple<ELEMS...>& tup)
{
    if constexpr (INDEX < sizeof...(ELEMS))
    {
        if (std::get<INDEX>(tup))
        {
            inc_tuple_bin_seq<INDEX - 1, ELEMS...>(tup);
        }
        std::get<INDEX>(tup) = !std::get<INDEX>(tup);
    }
}

std::string create_divider(const char* first, const char*  mid, const char*  div, const char*  last, int input_count, int output_count)
{
    std::string out;

    out += first;
    out += mid;
    for (int i = 0; i < input_count * 2; ++i)
    {
        out += mid;
    }
    out += div;
    out += mid;
    for (int i = 0; i < output_count * 2; ++i)
    {
        out += mid;
    }
    out += last;

    return out;
}

template<
    size_t INDEX=0,
    typename... ELEMS
>
std::stringstream get_tuple_strstrm(std::tuple<ELEMS...> tup)
{
    std::stringstream ss;
    if constexpr (INDEX < sizeof...(ELEMS))
    {
        ss << std::get<INDEX>(tup) << ' ' << get_tuple_strstrm<INDEX + 1, ELEMS...>(tup).str();
    }
    return ss;
}

template<
    typename RETURN,
    typename... INPUTS,
    typename std::enable_if<std::is_same<bool, typename std::common_type<INPUTS...>::type>::value, int>::type = 0
>
void print_truth_table(std::function<RETURN(INPUTS...)> logic_function)
{
    /* line characters */
    const char *h_line="\u2500", *v_line="\u2502";
    /* corner characters */
    const char *tl_corner="\u250c", *tr_corner="\u2510", *bl_corner="\u2514", *br_corner="\u2518";
    /* 3-way intersection */
    const char *t_int="\u252c", *l_int="\u251c", *r_int="\u2524", *b_int="\u2534";
    /* 4-way intersection */
    const char *m_int="\u253c";

    constexpr size_t ROW_COUNT = std::pow(2, sizeof...(INPUTS));

    constexpr size_t input_count = sizeof...(INPUTS);
    constexpr size_t output_count = sizeof(RETURN);

    std::cout << create_divider(tl_corner, h_line, t_int, tr_corner, input_count, output_count) << std::endl;

    std::tuple<INPUTS...> inputs;
    for (size_t i = 0; i < ROW_COUNT; ++i)
    {
        std::cout << v_line;
        std::cout << ' ' << get_tuple_strstrm(inputs).str() << v_line;
        RETURN out = std::apply(logic_function, inputs);
        if constexpr (std::is_same<bool, RETURN>::value)
        {
            std::cout << ' ' << out << ' ' << v_line << std::endl;
        }
        else
        {
            std::cout << ' ';
            for (int i = 0; i < out.size(); ++i)
            {
                std::cout << out[i] << ' ';
            }
            std::cout << v_line << std::endl;
        }
        inc_tuple_bin_seq<input_count - 1, INPUTS...>(inputs);
    }

    std::cout << create_divider(bl_corner, h_line, b_int, br_corner, input_count, output_count) << std::endl;
}

template<
    typename RETURN,
    typename... INPUTS,
    typename std::enable_if<std::is_same<bool, typename std::common_type<INPUTS...>::type>::value, int>::type = 0
>
void print_truth_table(RETURN(*logic_function)(INPUTS...))
{
    print_truth_table(std::function(logic_function));
}

int main(int argc, char** argv)
{
    print_truth_table(full_adder);
    return 0;
}