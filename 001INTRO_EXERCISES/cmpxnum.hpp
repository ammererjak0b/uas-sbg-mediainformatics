#include <iostream>

class complex_number
{
  public:
    double real_part;
    double imaginary_part;
  
    complex_number(const double real_part, const double imaginary_part = 0)
     : real_part(real_part), imaginary_part(imaginary_part)
    {
    }
    
    complex_number operator+(const complex_number &value) const
    {
      const auto sum_re = real_part + value.real_part;
      const auto sum_im = imaginary_part + value.imaginary_part;
      const complex_number sum(sum_re, sum_im);
      return sum;
    }
};

std::ostream &operator <<(std::ostream &os, const complex_number &value)
{
  return (os << value.real_part << " + " << value.imaginary_part << "j");
}
