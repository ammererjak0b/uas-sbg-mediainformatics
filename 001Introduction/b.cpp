#include <iostream>
#include <vector>
#include <algorithm>

#include "cmpxnum.hpp"

void Increment(std::vector<int> &numbers, const int value = 1)
{
  std::transform(numbers.begin(), numbers.end(), numbers.begin(),
                 [value](int &number)
                        {
                          return number + value;
                        });
}

template <typename T>
void PrintNumbers(const std::string &header, const std::vector<T> &numbers)
{
  std::cout << header << std::endl;
  for (const T &number : numbers)
    std::cout << number << std::endl;
}

int main(const int, const char * const[])
{
  std::vector<int> values(3, 2);
  PrintNumbers("Vorher (ganzzahlig):", values);
  Increment(values);
  PrintNumbers("Nachher (ganzzahlig):", values);
  
  const complex_number c(3, 2);
  std::vector<complex_number> complex_values(3, c);
  PrintNumbers("Vorher (komplex):", complex_values);
  //Increment(complex_values);
  PrintNumbers("Nachher (komplex):", complex_values);
  return 0;
}
