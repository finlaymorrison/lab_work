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

    complex(const angle& ang) :
        real(ang.mag() * std::cos(ang.ph())),
        img(ang.mag() * std::sin(ang.ph()))
    {}
    complex(angle&& ang) :
        real(ang.mag() * std::cos(ang.ph())),
        img(ang.mag() * std::sin(ang.ph()))
    {}
    complex& operator= (const angle& ang)
    {
        real = ang.mag() * std::cos(ang.ph());
        img = ang.mag() * std::sin(ang.ph());
        return *this;
    }
    complex& operator= (angle&& ang)
    {
        real = ang.mag() * std::cos(ang.ph());
        img = ang.mag() * std::sin(ang.ph());
        return *this;
    }

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
constexpr complex<Ty> operator+ (const complex<Ty>& c_num) noexcept
{
    return c_num;
}

template<typename Ty_cmplx, typename Ty_real, 
         typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() + Ty_real())> operator+ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() + re_num, c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real, 
         typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() + Ty_cmplx())> operator+ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
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
constexpr complex<Ty> operator- (const complex<Ty>& c_num) noexcept
{
    return {-c_num.re(), -c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real, 
         typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() - Ty_real())> operator- (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() - re_num, c_num.im()};
}

template<typename Ty_cmplx, typename Ty_real, 
         typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() - Ty_cmplx())> operator- (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
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

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() * Ty_real())> operator* (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() * re_num, c_num.im() * re_num};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() * Ty_cmplx())> operator* (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
{
    return {re_num * c_num.re(), re_num * c_num.im()};
}

/* Unary operator* to act as the conjugate operator */
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

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_cmplx() / Ty_real())> operator/ (const complex<Ty_cmplx>& c_num, const Ty_real& re_num) noexcept
{
    return {c_num.re() / re_num, c_num.im() / re_num};
}

template<typename Ty_cmplx, typename Ty_real, typename std::enable_if<std::is_arithmetic<Ty_real>::value, int>::type = 0>
constexpr complex<decltype(Ty_real() / Ty_cmplx())> operator/ (const Ty_real& re_num, const complex<Ty_cmplx>& c_num) noexcept
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

/* Outputs the complex number into the ostream passed in, in the form a+jb */
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const complex<Ty>& c_num)
{
    return os << c_num.re() << (c_num.im() < 0 ? '-' : '+') << std::abs(c_num.im()) << 'j';
}

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
    /* Narrowing to a signed type */
    return complex<long long int>(0, img);
}
inline constexpr complex<long long int> operator""_j (unsigned long long int img) noexcept
{
    /* Narrowing to a signed type */
    return complex<long long int>(0, img);
}

class angle
{
private:
    double magnitude, phase;
public:
    angle() = default;
    angle(double magnitude, double phase) :
        magnitude(magnitude), phase(phase)
    {}
    angle(const angle& ang) :
        magnitude(ang.magnitude), phase(ang.phase)
    {}
    angle(angle&& ang) :
        magnitude(ang.magnitude), phase(ang.phase)
    {}
    angle(const complex<double>& cartesian) :
        magnitude(cartesian.abs()), phase(cartesian.arg())
    {}
    angle(complex<double>&& cartesian) :
        magnitude(cartesian.abs()), phase(cartesian.arg())
    {}

    angle& operator= (const angle& ang)
    {
        magnitude = ang.magnitude;
        phase = ang.phase;
        return *this;
    }
    angle& operator= (angle&& ang)
    {
        magnitude = ang.magnitude;
        phase = ang.phase;
        return *this;
    }

    angle& operator= (const complex<double>& cartesian)
    {
        magnitude = cartesian.abs();
        phase = cartesian.arg();
        return *this;
    }
    angle& operator= (complex<double>&& cartesian)
    {
        magnitude = cartesian.abs();
        phase = cartesian.arg();
        return *this;
    }

    double& mag()
    {
        return magnitude;
    }
    double mag() const
    {
        return magnitude;
    }
    double& ph()
    {
        return phase;
    }
    double ph() const
    {
        return phase;
    }
};

angle operator* (const angle& a, const angle& b)
{
    return {a.mag() * b.mag(), a.ph() + b.ph()};
}

angle operator/ (const angle& a, const angle& b)
{
    return {a.mag() / b.mag(), a.ph() - b.ph()};
}

constexpr complex<double> get_series_rlc_impedance(double r, double l, double c, double f) noexcept;

struct time_domain
{
    double magnitude, phase;
    constexpr time_domain(double magnitude, double phase) noexcept :
        magnitude(magnitude), phase(phase)
    {}
};

std::ostream& operator<< (std::ostream& os, time_domain wave)
{
    return os << wave.magnitude << "\u2220" << wave.phase;
}

class series_rlc
{
private:
    double r, l, c;
public:
    series_rlc() = default;
    constexpr series_rlc(double r, double l, double c) noexcept :
        r(r), l(l), c(c)
    {}
    constexpr series_rlc(const series_rlc& circuit) noexcept :
        r(circuit.r), l(circuit.l), c(circuit.c)
    {}
    constexpr series_rlc(series_rlc&& circuit) noexcept :
        r(circuit.r), l(circuit.l), c(circuit.c)
    {}
    ~series_rlc() = default;

    constexpr series_rlc& operator= (const series_rlc& circuit) noexcept
    {
        r = circuit.r;
        l = circuit.l;
        c = circuit.c;
        return *this;
    }
    constexpr series_rlc& operator= (series_rlc&& circuit) noexcept
    {
        r = circuit.r;
        l = circuit.l;
        c = circuit.c;
        return *this;
    }

    complex<double> get_complex_current(double v, double f) noexcept
    {
        return complex<double>(v, 0.0) / get_series_rlc_impedance(r, l, c, f);
    }
    time_domain get_current(double v, double f) noexcept
    {
        complex<double> current = get_complex_current(v, f);
        return {current.abs(), current.arg()};
    }
};

std::istream& operator>> (std::istream& is, series_rlc& circuit)
{
    double r, l, c;
    is >> r >> l >> c;
    circuit = series_rlc(r, l, c);
    return is;
}

constexpr complex<double> get_series_rlc_impedance(double r, double l, double c, double f) noexcept
{
    double real=r;
    double img = 2 * M_PI * f * l - 1 / (2 * M_PI * f * c);
    return {real, img};
}

int main(int argc, char** argv)
{
    std::cout << "Input R, L and C: ";
    series_rlc circuit;
    std::cin >> circuit;
    std::cout << "Magnitude of Voltage Source: ";
    double magnitude;
    std::cin >> magnitude;
    std::cout << "Frequency of Voltage Source: ";
    double frequency;
    std::cin >> frequency;
    std::cout << circuit.get_current(magnitude, frequency) << std::endl;
    return 0;
}