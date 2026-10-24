/*
- AUTHOR: Jakob Ammerer
- TASK: LBEL01b)
- TODO: 
    replace all white pixels with black pixels before writing output file 
    (8-BIT-RGB Pictures which means the PixelDataType is cv::Vec3b).
    Use overload operators from parentclass.
    OpenCV is BGR not RGB which makes no diffrence in this case white: (255 255 255) and black (0 0 0)

- AI USAGE: Claude Sonnet 5.5
  - [AI_0] Asked why OpenCV uses BGR instead of RGB
  - [AI_1] (TASK B) Asked why it points behind the last px not to the last exactly: because it cannot tell the last px is really the lastone, but it can point behind the last one, which is a null value so we know for sure thats the last. 
- SOURCES: 
  - Aufgabe_Einfuehrung_OpenCV.pdf,   
  - [0] https://docs.opencv.org/4.13.0/db/deb/tutorial_display_image.html. (display image: imread, waitkey, imshow, im write...)
    - [0,1]: imread() https://docs.opencv.org/4.13.0/d4/da8/group__imgcodecs.html#gaffb68fce322c6e52841d7d9357b9ad2d
  - [1] https://docs.opencv.org/4.13.0/d3/d63/classcv_1_1Mat.html#a03d2a2570d06dcae378f788725789aa4 full image clone: clone()
  Task B specific: 
  - [2] https://en.cppreference.com/cpp/algorithm/replace I use replace if: Replaces the elements in the target range [first, last) with new_value if they satisfy specific criteria
  - [3] https://www.geeksforgeeks.org/cpp/stdreplace-stdreplace_if-c/ further explantation replace if
  - [4] https://docs.opencv.org/4.13.0/dc/d84/group__core__basic.html#ga7e6060c0b8d48459964df6e1eb524c03 (Vec3b)

- NOTES:
  - std::replace_if() blueprint:
      Param 1: first, where search starts. (first pixel)
      Param 2: last, where search ends. (behin last pixel)
      Param 3: predicate, test per elemente (our lamda)
      Param 4: if predicate is true, do this (make white px black)  
*/

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" // imshow, waitKey
#include "opencv2/imgcodecs.hpp" // imread, imwrite
#include <algorithm> // replace_if() 

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

  // begin points to first px, end points behind last px, so it knows where to end. [2] (Example Code Section), [AI_1]
  std::replace_if(    
    outputImage.begin<cv::Vec3b>(), outputImage.end<cv::Vec3b>(), // this combo sets the range for the replace_if function. so it goes over every px in that range
    
    // anonymous lamda func same as in c# [capture list]: what is seen from outside, (params) replace if calls this func foreach pixel
    [](const cv::Vec3b &pixel){      
      bool isWhite = (pixel == cv::Vec3b(255, 255, 255)); 
      return isWhite;
    },
    cv::Vec3b(0,0,0) // replaces white pixels if black 
  );

  cv::imwrite(outputImagePath, outputImage); // Saves an image to a specified file. [0]
  
  cv::imshow("output", outputImage); // Displays an image in the specified window.[0]

  cv::waitKey(0); // waits for keyboard input (infinite) because we use 0. We could also enter a delay in ms [0]
  
  return 0;
}
