#include <iostream>
#include "opencv2/core.hpp"

int main(const int argc, const char * const argv[])
{
  std::cout << cv::getBuildInformation() << std::endl;
  return 0;
}
