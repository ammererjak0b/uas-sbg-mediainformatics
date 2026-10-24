/*
- AUTHOR: Jakob Ammerer
- TASK: LBEL00b)

- AI USAGE: Claude Sonnet 5.5
  - was used to verify my results
- SOURCES: 
  - Aufgabe_Einfuehrung_OpenCV.pdf, 
  - https://docs.opencv.org/4.13.0/d1/dfb/intro.html
  - https://docs.opencv.org/4.13.0/d6/d6d/tutorial_mat_the_basic_image_container.html
  - https://docs.opencv.org/4.13.0/d3/d63/classcv_1_1Mat.html#details
*/

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
