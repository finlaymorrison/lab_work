
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

std::array<bool, 8> create_bit_array(int8_t num) noexcept
{
   std::array<bool, 8> out = {0,0,0,0,0,0,0,0};
   int i = 0;
   for (int i = 0; i < 8; ++i)
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

int main(int argc, char** argv)
{
   int a, b;
   bool ci, overflow;
   char op;

   std::cout << "Input your first number (A): ";
   std::cin >> a;
   std::cout << "Input your first number (B): ";
   std::cin >> b;
   std::cout << "Select operation (+ or -): ";
   std::cin >> op;
  
   std::cout << a << op << b << '\n';

   std::array<bool, 8> a_bits = create_bit_array(a);
   std::cout << "Corresponding value A in binary: " << a_bits << '\n';
   std::array<bool, 8> b_bits = create_bit_array(b);
   std::cout << "Corresponding value B in binary: " << b_bits << '\n';

   if (op == '+')
   {
       ci = false;
   }
   else
   {
       ci = true;
       invert(b_bits);
   }


   std::array<bool, 8> output = bit_adder<8>(a_bits, b_bits, ci, overflow);
   if (output[7])
   {
       std::cout << "Its a negative number, need to convert from 2's complement to decimal\n";
       invert(output);
       bool carry=true, ov=false;
       output = bit_adder<8>(output, {0,0,0,0,0,0,0,0}, carry, ov);
       std::cout << output << '\n' << '-';
   }
   else
   {
       std::cout << output << std::endl;
   }

   std::cout << static_cast<int>(bit_array_to_num(output)) << '\n';
   std::cout << "Overflow: " << std::boolalpha << ci << std::endl;


   return 0;
}