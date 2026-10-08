#include <iostream>
#include "opencv2/core.hpp"

int main(const int argc, const char * const argv[])
{
  const cv::Mat A = cv::Mat_<double>({2, 2}, {1, 2, 3, 4}); // double, cause mayb float value
  const cv::Mat B = cv::Mat_<double>({2, 2}, {4, -3, -2, 1});

  const cv::Mat product = A * B; // give you the matrix product, not elementwise multiplication
  const cv::Mat inverse = product.inv();

  // operator overload print way
  std::cout << "A*B:" << std::endl << product << std::endl;
  std::cout << "inverse:" << std::endl << inverse << std::endl;

  // range based output
  
  std::cout << "A*B (elements): ";
  for (const auto &value : cv::Mat_<double>(product))
  {
    std::cout << value << " ";
  }

  std::cout << std::endl;

  std::cout << "inverse (elements): ";
  for (const auto &value : cv::Mat_<double>(inverse))
  {
    std::cout << value << " ";
  }
  

  return 0;
}
