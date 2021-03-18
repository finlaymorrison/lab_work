/*
 * Project: p4
 * File: p4/complex.hpp
 * -----
 * File Created: Saturday, 20th February 2021 4:45:51 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:30:52 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <iostream>
#include <type_traits>
#include <cmath>

namespace math {

template<typename Ty>
class complex
{
private:

    Ty real, img;

public:

    complex() = default;
    constexpr complex(Ty real, Ty img) noexcept :
        real(real), img(img)
    {}
    template<typename Ty_cmplx>
    constexpr complex(const complex<Ty_cmplx>& c_num) noexcept :
        real(c_num.re()), img(c_num.im())
    {}
    template<typename Ty_cmplx>
    constexpr complex(complex<Ty_cmplx>&& c_num) noexcept :
        real(c_num.re()), img(c_num.im())
    {}
    ~complex() = default;

    template<typename Ty_cmplx>
    constexpr complex& operator= (const complex<Ty_cmplx>& c_num) noexcept
    {
        real = c_num.re(); 
        img = c_num.im();
        return *this;
    }
    template<typename Ty_cmplx>
    constexpr complex& operator= (complex<Ty_cmplx>&& c_num) noexcept
    {
        real = c_num.re(); 
        img = c_num.im();
        return *this;
    }

    inline constexpr complex<Ty> conj() const noexcept
    {
        return {real, -img};
    }

    inline Ty abs() const
    {
        return std::sqrt(real * real + img * img);
    }

    inline Ty arg() const
    {
        return std::atan2(img, real);
    }

    inline constexpr Ty& re() noexcept
    {
       return real;
    }
    inline constexpr Ty re() const noexcept
    {
       return real;
    }

    inline constexpr Ty& im() noexcept
    {
       return img;
    }
    inline constexpr Ty im() const noexcept
    {
       return img;
    }
};

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() + Ty_b())> operator+ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() + Ty_b()) ret_t;
    const ret_t real = a.re() + b.re();
    const ret_t img = a.im() + b.im();
    return {real, img};
}

template<typename Ty>
inline constexpr complex<Ty> operator+ (const complex<Ty>& c_num) noexcept
{
    return c_num;
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() + Ty_real())> operator+ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() + re_num, c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_real() + Ty_cmplx())> operator+ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {c_num.re() + re_num, c_num.im()};
}

template<typename Ty_a, typename  Ty_b>
constexpr complex<decltype(Ty_a() - Ty_b())> operator- (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() - Ty_b()) ret_t;
    const ret_t real = a.re() - b.re();
    const ret_t img = a.im() - b.im();
    return {real, img};
}

template<typename Ty>
inline constexpr complex<Ty> operator- (const complex<Ty>& c_num) noexcept
{
    return {-c_num.re(), -c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() - Ty_real())> operator- (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() - re_num, c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_real() - Ty_cmplx())> operator- (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {re_num - c_num.re(), -c_num.im()};
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() * Ty_b())> operator* (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() * Ty_b()) ret_t;
    const ret_t real = a.re() * b.re() - a.im() * b.im();
    const ret_t img = a.re() * b.im() + a.im() * b.re();
    return {real, img};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() * Ty_real())> operator* (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() * re_num, c_num.im() * re_num};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_real() * Ty_cmplx())> operator* (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {re_num * c_num.re(), re_num * c_num.im()};
}

template<typename Ty>
inline constexpr complex<Ty> operator* (const complex<Ty>& c_num) noexcept
{
    return {c_num.re(), -c_num.im()};
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() / Ty_b())> operator/ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() / Ty_b()) ret_t;
    const ret_t quotient = b.re() * b.re() + b.im() * b.im();
    const ret_t real = (a.re() * b.re() + a.im() * b.im()) / quotient;
    const ret_t img = (b.re() * a.im() - a.re() * b.im()) / quotient;
    return {real, img};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() / Ty_real())> operator/ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() / re_num, c_num.im() / re_num};
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_real() / Ty_cmplx())> operator/ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return complex<Ty_real>(re_num, 0) / c_num;
}

template<typename Ty>
inline constexpr bool operator== (const complex<Ty>& a, const complex<Ty>& b) noexcept
{
    return a.re() == b.re() && a.im() == b.im();
}

template<typename Ty>
inline constexpr bool operator!= (const complex<Ty>& a, const complex<Ty>& b) noexcept
{
    return !(a==b);
}

template<typename Ty>
std::ostream& operator<<(std::ostream& os, const complex<Ty>& c_num)
{
    return os << c_num.re() << (c_num.im() < 0 ? '-' : '+') << std::abs(c_num.im()) << 'j';
}

namespace literals {

inline constexpr complex<long double> operator""_i (long double img) noexcept
{
    return complex<long double>(0.0, img);
}
inline constexpr complex<long double> operator""_j (long double img) noexcept
{
    return complex<long double>(0.0, img);
}

inline constexpr complex<long long int> operator""_i (unsigned long long int img) noexcept
{
    return complex<long long int>(0, img);
}
inline constexpr complex<long long int> operator""_j (unsigned long long int img) noexcept
{
    return complex<long long int>(0, img);
}

}

template<typename T_a, typename T_b>
inline constexpr complex<decltype(T_a() + T_b())>& operator+= (complex<T_a>& a, const complex<T_b>& b) noexcept
{
    a.re() += b.re();
    a.im() += b.im();
    return a;
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() + Ty_real())>& operator+= (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    c_num.re() += re_num;
    return c_num;
}

template<typename T_a, typename T_b>
inline constexpr complex<decltype(T_a() - T_b())>& operator-= (complex<T_a>& a, const complex<T_b>& b) noexcept
{
    a.re() -= b.re();
    a.im() -= b.im();
    return a;
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() - Ty_real())>& operator-= (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    c_num.re() -= re_num;
    return c_num;
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() * Ty_b())>& operator*= (complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() * Ty_b()) ret_t;
    const ret_t real_temp = a.re();
    a.re() = a.re() * b.re() - a.im() * b.im();
    a.im() = real_temp * b.im() + a.im() * b.re();
    return a;
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() * Ty_real())>& operator*= (complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    c_num.re() *= re_num;
    c_num.im() *= re_num;
    return c_num;
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() / Ty_b())>& operator/= (complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() / Ty_b()) ret_t;
    const ret_t quotient = b.re() * b.re() + b.im() * b.im();
    const ret_t temp_real = a.re();
    a.re() = (a.re() * b.re() + a.im() * b.im()) / quotient;
    a.im() = (b.re() * a.im() - temp_real * b.im()) / quotient;
    return a;
}

template<typename Ty_cmplx, typename Ty_real>
inline constexpr complex<decltype(Ty_cmplx() / Ty_real())>& operator/= (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    c_num.re() /= re_num;
    c_num.im() /= re_num;
    return c_num;
}

template<typename Ty>
inline constexpr Ty re(const complex<Ty>& c_num) noexcept
{
    return c_num.re();
}
template<typename Ty>
inline constexpr Ty& re(complex<Ty>& c_num) noexcept
{
    return c_num.re();
}

template<typename Ty>
inline constexpr Ty im(const complex<Ty>& c_num) noexcept
{
    return c_num.im();
}
template<typename Ty>
inline constexpr Ty& im(complex<Ty>& c_num) noexcept
{
    return c_num.im();
}

template<typename Ty>
inline constexpr complex<Ty> conj(const complex<Ty>& c_num) noexcept
{
    return c_num.conj();
}

template<typename Ty>
inline Ty abs(const complex<Ty>& c_num)
{
    return c_num.abs();
}

template<typename Ty>
inline Ty arg(const complex<Ty>& c_num)
{
    return c_num.arg();
}

}