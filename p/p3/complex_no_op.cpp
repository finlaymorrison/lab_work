#include <cmath>
#include <type_traits>

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
   constexpr complex(const complex<Ty>& c_num) noexcept :
       real(c_num.real), img(c_num.img)
   {}
   constexpr complex(complex<Ty>&& c_num) noexcept :
       real(c_num.real), img(c_num.img)
   {}

   /* Default destructor, no resources to free */
   ~complex() = default;

   /* Assignment operators */
   constexpr complex& operator= (const complex<Ty>& c_num) noexcept
   {
       real = c_num.real; img = c_num.img;
       return *this;
   }
   constexpr complex& operator= (complex<Ty>&& c_num) noexcept
   {
       real = c_num.real; img = c_num.img;
       return *this;
   }

   /* Operators defined as member functions */

   /* Returns the calling object plus c_num */
   constexpr complex<Ty> add(const complex<Ty>& c_num) const noexcept
   {
       Ty ret_real = real + c_num.real;
       Ty ret_img = img + c_num.img;
       return {ret_real, ret_img};
   }

   /* Returns the calling object minus c_num */
   constexpr complex<Ty> sub(const complex<Ty>& c_num) const noexcept
   {
       Ty ret_real = real - c_num.real;
       Ty ret_img = img - c_num.img;
       return {ret_real, ret_img};
   }

   /* Returns the calling object multiplied by c_num */
   constexpr complex<Ty> mult(const complex<Ty>& c_num) const noexcept
   {
       Ty ret_real = real * c_num.real - img * c_num.img;
       Ty ret_img = real * c_num.img + c_num.real * img;
       return {ret_real, ret_img};
   }

   /* Returns the calling object multiplied by c_num */
   constexpr complex<Ty> div(const complex<Ty>& c_num) const noexcept
   {
       Ty quotient = c_num.real * c_num.real + c_num.img * c_num.img;
       Ty ret_real = (real * c_num.real + img * c_num.img) / quotient;
       Ty ret_img = (c_num.real * img - real * c_num.img) / quotient;
       return {ret_real, ret_img};
   }

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
   /* Returns whether c_num is the same as the calling object */
   inline constexpr bool equal(const complex<Ty> c_num) noexcept
   {
       return real == c_num.real && img = c_num.img;
   }
};