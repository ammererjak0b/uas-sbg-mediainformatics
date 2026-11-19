/*
- AUTHOR: Jakob Ammerer
- TASK: LBGE00a)
- TODO:
    Programm: 1 Argument = Videopfad. Frames mit cv::VideoCapture laden, in Fenster abspielen, annähernd echtzeitkorrekt (Wartezeit pro Frame). Beliebige Taste bricht ab.

- AI USAGE: Claude Sonnet 5.5

- SOURCES:
  -[0] https://docs.opencv.org/3.4.20/d8/dfe/classcv_1_1VideoCapture.html
  -[1] https://stackoverflow.com/questions/49048111/how-to-get-the-duration-of-video-using-opencv (get frame length)
  -[1.1] https://docs.opencv.org/3.4.20/d4/d15/group__videoio__flags__base.html#gaeb8dd9c89c10a5c63c139bf7c4f5704d

- NOTES:
  This Snippet is largely inspired by this: https://docs.opencv.org/3.4.20/d8/dfe/classcv_1_1VideoCapture.html#aa6480e6972ef4c00d74814ec841a2939

*/

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp" // VideoCapture
#include "opencv2/highgui.hpp" // imshow, waitKey

int main(const int argc, const char * const argv[])
{
  if(argc != 2){
    std::cerr << "Usage: <path_to_image>" << std::endl;
    return 1;
  }
 
  std::string pathToFile = argv[1];
  cv::Mat frame;
  cv::VideoCapture cap;

  // [1] [1.1] possible params. used fps and and framcount to get the duration.
  auto fps = cap.get(CAP_PROP_FPS);
  auto frameCount = cap.get(CAP_PROP_FRAME_COUNT);
  duration = (frameCount / fps);
  cap.open(pathToFile); // open file
  
  // check if open was success
  if(!(cap.isOpened())){
    std::cerr << "Error: Could not open file" << std::endl;
    return 2;
  }

  for (;;){
      // wait for a new frame from camera and store it into 'frame'
      cap.read(frame);

      // check if we succeeded
      if (frame.empty()) {
        cerr << "ERROR! blank frame grabbed\n";
        break;
      }  

      // show live and wait for a key with timeout long enough to show images
      imshow("Live", frame);
      if (waitKey() >= 0){ // todo: get the 
        break;
      }  
  }
  
  return 0;
}
