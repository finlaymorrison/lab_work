#include <iostream>
#include <type_traits>
#include <cmath>
#include <iomanip>

#include <ccomplex>

/* Templating to allow for the class to represent a complex number of any numeric type */
template<
    typename Ty,
    typename std::enable_if<std::is_arithmetic<Ty>::value, int>::type = 0
>
class complex
{
private:

    /* Member variables to hold the current state of the complex number */
    Ty real, img;

public:

    /* Constructors */
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

    /* Default destructor, no resources to free */
    ~complex() = default;

    /* Assignment operators */
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

    /* Declaring operators as friend functions so they are able to access the private members directly */

    template<typename Ty_a, typename Ty_b>
    constexpr friend complex<decltype(Ty_a() + Ty_b())> operator+ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept;
    template<typename Ty_op>
    constexpr friend complex<Ty_op> operator+ (const complex<Ty_op>& c_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_cmplx() + Ty_real())> operator+ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_real() + Ty_cmplx())> operator+ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept;

    template<typename Ty_a, typename  Ty_b>
    constexpr friend complex<decltype(Ty_a() - Ty_b())> operator- (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept;
    template<typename Ty_op>
    constexpr friend complex<Ty_op> operator- (const complex<Ty_op>& c_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_cmplx() - Ty_real())> operator- (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_real() - Ty_cmplx())> operator- (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept;
    
    template<typename Ty_a, typename Ty_b>
    constexpr friend complex<decltype(Ty_a() * Ty_b())> operator* (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_cmplx() * Ty_real())> operator* (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_real() * Ty_cmplx())> operator* (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept;
    template<typename Ty_op>
    constexpr friend complex<Ty_op> operator* (const complex<Ty_op>& c_num) noexcept; /* conjugate function */

    template<typename Ty_a, typename Ty_b>
    constexpr friend complex<decltype(Ty_a() / Ty_b())> operator/ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_cmplx() / Ty_real())> operator/ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept;
    template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type>
    constexpr friend complex<decltype(Ty_real() / Ty_cmplx())> operator/ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept;

    template<typename Ty_op>
    inline constexpr friend bool operator== (const complex<Ty_op>& a, const complex<Ty_op>& b) noexcept;
    template<typename Ty_op>
    inline constexpr friend bool operator!= (const complex<Ty_op>& a, const complex<Ty_op>& b) noexcept;

    template<typename Ty_op>
    friend std::ostream& operator<< (std::ostream& os, const complex<Ty_op>& c_num);

    /* Returns the conjugate of the calling object */
    inline constexpr complex<Ty> conj() const noexcept
    {
        return {real, -img};
    }

    /* Returns the absolute value of the calling object */
    inline Ty abs() const
    {
        return std::sqrt(real * real + img * img);
    }

    /* Returns the argument of the calling object in polar space */
    inline Ty arg() const
    {
        return std::atan2(img, real);
    }

    /* Returns the real part of the calling object (non-const version) */
    inline constexpr Ty& re() noexcept
    {
       return real;
    }
    /* Returns the real part of the calling object (const version) */
    inline constexpr Ty re() const noexcept
    {
       return real;
    }

    /* Returns the imaginary part of the calling object (non-const version) */
    inline constexpr Ty& im() noexcept
    {
       return img;
    }
    /* Returns the imaginary part of the calling object (const version) */
    inline constexpr Ty im() const noexcept
    {
       return img;
    }
};

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() + Ty_b())> operator+ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() + Ty_b()) ret_t;
    const ret_t real = a.real + b.real;
    const ret_t img = a.img + b.img;
    return {real, img};
}

template<typename Ty>
constexpr complex<Ty> operator+ (const complex<Ty>& c_num) noexcept
{
    return c_num;
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() + Ty_real())> operator+ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.real + re_num, c_num.img};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() + Ty_cmplx())> operator+ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {c_num.real + re_num, c_num.img};
}

template<typename Ty_a, typename  Ty_b>
constexpr complex<decltype(Ty_a() - Ty_b())> operator- (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() - Ty_b()) ret_t;
    const ret_t real = a.real - b.real;
    const ret_t img = a.img - b.img;
    return {real, img};
}

template<typename Ty>
constexpr complex<Ty> operator- (const complex<Ty>& c_num) noexcept
{
    return {-c_num.real, -c_num.img};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() - Ty_real())> operator- (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.real - re_num, c_num.img};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() - Ty_cmplx())> operator- (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {re_num - c_num.real, -c_num.img};
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() * Ty_b())> operator* (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() * Ty_b()) ret_t;
    const ret_t real = a.real * b.real - a.img * b.img;
    const ret_t img = a.real * b.img + a.img * b.real;
    return {real, img};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() * Ty_real())> operator* (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.real * re_num, c_num.img * re_num};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() * Ty_cmplx())> operator* (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {re_num * c_num.real, re_num * c_num.img};
}

/* Unary operator* to act as the conjugate operator */
template<typename Ty>
inline constexpr complex<Ty> operator* (const complex<Ty>& c_num) noexcept
{
    return {c_num.real, -c_num.img};
}

template<typename Ty_a, typename Ty_b>
constexpr complex<decltype(Ty_a() / Ty_b())> operator/ (const complex<Ty_a>& a, const complex<Ty_b>& b) noexcept
{
    typedef decltype(Ty_a() / Ty_b()) ret_t;
    const ret_t quotient = b.real * b.real + b.img * b.img;
    const ret_t real = (a.real * b.real + a.img * b.img) / quotient;
    const ret_t img = (b.real * a.img - a.real * b.img) / quotient;
    return {real, img};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() / Ty_real())> operator/ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.real / re_num, c_num.img / re_num};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() / Ty_cmplx())> operator/ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return complex<Ty_real>(re_num, 0) / c_num;
}

template<typename Ty>
inline constexpr bool operator== (const complex<Ty>& a, const complex<Ty>& b) noexcept
{
    return a.real == b.real && a.img == b.img;
}

template<typename Ty>
inline constexpr bool operator!= (const complex<Ty>& a, const complex<Ty>& b) noexcept
{
    return !(a==b);
}

/* Outputs the complex number into the ostream passed in, in the form a+jb */
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const complex<Ty>& c_num)
{
    return os << c_num.real << (c_num.img < 0 ? '-' : '+') << std::abs(c_num.img) << 'j';
}

inline constexpr complex<long double> operator""_i (long double img) noexcept
{
    return complex<long double>(0, img);
}
inline constexpr complex<long double> operator""_j (long double img) noexcept
{
    return complex<long double>(0, img);
}

inline constexpr complex<long long int> operator""_i (unsigned long long int img) noexcept
{
    /* Narrowing to a signed type */
    return complex<long long int>(0, img);
}
inline constexpr complex<long long int> operator""_j (unsigned long long int img) noexcept
{
    /* Narrowing to a signed type */
    return complex<long long int>(0, img);
}

complex<double> get_series_rlc_impedance(double r, double l, double c, double f)
{
    double real=r, img=0;
    img += 2 * M_PI * f * l;
    img += 1 / (2 * M_PI * f * c);
    return {real, img};
}

int main(int argc, char** argv)
{
    complex<double> c0(4.0, 4.6);
    complex<float> c1(4.0, 4.6);
    complex<long double> c2 = 1 + 2.2_i;
    complex<double> c3 = 2 / c2;
    std::cout << c3 << std::endl;
    return 0;
}