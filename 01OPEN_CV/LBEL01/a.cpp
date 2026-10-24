/*
- AUTHOR: Jakob Ammerer
- TASK: LBEL01a)

- AI USAGE: Claude Sonnet 5.5
  - [AI_0] Asked why OpenCV uses BGR instead of RGB
- SOURCES: 
  - Aufgabe_Einfuehrung_OpenCV.pdf,   
  - [0] https://docs.opencv.org/4.13.0/db/deb/tutorial_display_image.html. (display image: imread, waitkey, imshow, im write...)
    - [0,1]: imread() https://docs.opencv.org/4.13.0/d4/da8/group__imgcodecs.html#gaffb68fce322c6e52841d7d9357b9ad2d
  - [1] https://docs.opencv.org/4.13.0/d3/d63/classcv_1_1Mat.html#a03d2a2570d06dcae378f788725789aa4 full image clone: clone()

*/

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" // imshow, waitKey
#include "opencv2/imgcodecs.hpp" // imread, imwrite

int main(const int argc, const char * const argv[])
{
  if(argc != 3){
    std::cerr << "usage: inputImage> <outputImage" << std::endl;
    return 1;
  }

  std::string inputImagePath = argv[1];
  std::string outputImagePath = argv[2];

  const auto inputImage = cv::imread(inputImagePath); // OpenCV stores channels in BGR not in RGB (historical reasons, bc in 90s format saved it in BGR e.g Window Bitmaps) [0,1] [AI_0]

  if(inputImage.empty()){
    std::cerr << "could not read image: " << argv[1] << std::endl;
    return 1;
  }

  auto outputImage = inputImage.clone(); // clone() Creates a full copy of the array and the underlying data.[1]
  
  cv::imwrite(outputImagePath, outputImage); // Saves an image to a specified file. [0]

  cv::imshow("output", outputImage); // Displays an image in the specified window.[0]

  cv::waitKey(0); // waits for keyboard input (infinite) because we use 0. We could also enter a delay in ms [0]
  
  return 0;
}
