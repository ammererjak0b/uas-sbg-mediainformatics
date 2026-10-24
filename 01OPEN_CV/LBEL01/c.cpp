/*
- AUTHOR: Jakob Ammerer
- TASK: LBEL01c)
- Angabe, Draw Circle, Rectangle, Lines, Name

- AI USAGE: Claude Sonnet 5.5
  - [AI_0] Asked why OpenCV uses BGR instead of RGB  
- SOURCES: 
  - Aufgabe_Einfuehrung_OpenCV.pdf,   
  - [0] https://docs.opencv.org/4.13.0/db/deb/tutorial_display_image.html. (display image: imread, waitkey, imshow, im write...)
    - [0,1]: imread() https://docs.opencv.org/4.13.0/d4/da8/group__imgcodecs.html#gaffb68fce322c6e52841d7d9357b9ad2d
  - [1] https://docs.opencv.org/4.13.0/d3/d63/classcv_1_1Mat.html#a03d2a2570d06dcae378f788725789aa4 full image clone: clone()
  Task C specific: 
  - [2]: https://docs.opencv.org/4.13.0/d3/d96/tutorial_basic_geometric_drawing.html (Point, Scalar) tutorial on how to draw
  - [3]: https://docs.opencv.org/4.13.0/d6/d6e/group__imgproc__draw.html#ga07d2f74cadcf8e305e810ce8eed13bc9 Basic Shapes, lines, circle, rectangle
  - [4]: https://docs.opencv.org/4.13.0/d6/d6e/group__imgproc__draw.html#ga5126f47f883d730f633d74f07456c576 putText function
  NOTES c): 
    Center point calc: x / 2 und y / 2 in this case x = 600/2 and y = 739 / 2. Y is uneven, due to int it rounds down, so it is half a px of on the y axis.
*/

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp" // imshow, waitKey
#include "opencv2/imgcodecs.hpp" // imread, imwrite
#include "opencv2/imgproc.hpp"

int main(const int argc, const char * const argv[])
{
  if(argc != 3){
    std::cerr << "usage: inputImage> <outputImage" << std::endl;
    return 1;
  }

  const cv::Scalar red(0,0,255); 
  const cv::Scalar green(0, 255, 0);
  const cv::Scalar blue(255, 0, 0);
  const cv::Scalar black(0, 0, 0);

  const int radius = 50; // Red Circle Radius 50px
  const int lineThickness = 3; // thickness for every object 3px
  
  std::string inputImagePath = argv[1];
  std::string outputImagePath = argv[2];

  const auto inputImage = cv::imread(inputImagePath); // OpenCV stores channels in BGR not in RGB (historical reasons, bc in 90s format saved it in BGR e.g Window Bitmaps) [0,1] [AI_0]

  if(inputImage.empty()){
    std::cerr << "could not read image: " << argv[1] << std::endl;
    return 1;
  }

  auto outputImage = inputImage.clone(); // clone() Creates a full copy of the array and the underlying data.[1]

  const auto center = cv::Point(outputImage.cols / 2, outputImage.rows / 2); // gets center point of output image
  
  // Red Circle center of pic, radius 50px, color red, thickness 3px
  cv::circle(outputImage, center, radius, red, lineThickness); 

  // Rectangle: Around the circle, touches circle on all 4 sides, color green, thickness 3px
  const cv::Point topLeft(center.x - radius, center.y -radius);
  const cv::Point bottomRight(center.x + radius, center.y +radius);
  cv::rectangle(outputImage, topLeft, bottomRight, green, lineThickness);

  // Vertical line: blue, thickness 3 splitting the rectangle.
  const cv::Point yTop(center.x, topLeft.y);
  const cv::Point yBottom(center.x, bottomRight.y);
  cv::line(outputImage, yTop, yBottom, blue, lineThickness);

  // Horizontal line:
  const cv::Point xLeft(topLeft.x, center.y);
  const cv::Point xRight(bottomRight.x, center.y);
  cv::line(outputImage, xLeft, xRight, blue, lineThickness);

  // Write name
  cv::putText(outputImage, "Jakob Ammerer", cv::Point(100, 100), cv::FONT_HERSHEY_COMPLEX, 1, black, lineThickness); // similar to example call of putText docu [4]

  cv::imwrite(outputImagePath, outputImage); // Saves an image to a specified file. [0]

  cv::imshow("output", outputImage); // Displays an image in the specified window.[0]

  cv::waitKey(0); // waits for keyboard input (infinite) because we use 0. We could also enter a delay in ms [0]
  
  return 0;
}

