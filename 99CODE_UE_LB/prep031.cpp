#include <opencv2/opencv.hpp>

int main(const int, const char * const[])
{
    scv::Mat fromFile = cv::imread("left.png", cv::IMREAD_COLOR); // aus Datei laden, BGR, 8 Bit

    cv::Mat blank(480, 640, CV_8UC3, cv::Scalar(0, 0, 0)); // rows, cols, Typ, Füllwert

    uchar buffer[480 * 640]; // eigener Pixelspeicher
    
    cv::Mat wrapped(480, 640, CV_8UC1, buffer); // Header auf fremden Speicher, keine Kopie

    blank.at<cv::Vec3b>(10, 20) = cv::Vec3b(255, 0, 0); // Pixel (y=10, x=20) setzen, Reihenfolge B,G,R
    
  return 0;
}
