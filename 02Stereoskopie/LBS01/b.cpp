/*
- AUTHOR: Jakob Ammerer
- TASK: LBS01b)
- TODO: 
    Passen Sie Ihr Programm aus a) ¨uber die Parameter des Stereo-Matchers derart an, dass das erzeugte Disparit¨atsbild Ihrer Meinung nach besser wird.
    Wenden Sie Ihr Programm außerdem, vorbereitend auf das Folgebeispiel, auf die zur Verf¨ugung gestellten, nicht rektifizierten Testbilder an.
    Info: Derzeite Values der Parameter sind meiner Meinung nach die besten "parameter. Mehr dazu in Doku" 
- AI USAGE: Claude Sonnet 5.5
    - [AI-1]: Explained Param "preFilterCap" to me: 
        Before the comparision the Helligkeitsaenderung shifted to the righ is calculated.
        Everything above preFilterCap or under "-preFilterCap" is cut to this value.
        This param is responsible, that a hard contrast cut is not valued uebermaesig viel at the matching process.
    -[AI-2]: 
        Hab versucht die Parameter so zu tweaken, damit das Bild meiner Meinung nach gut aussieht. Ich hab verschieden Durchläufe gemacht. Einen dieser Durchläufe habe ich mit den lt. "Claude" optimalsten Parametern gemacht.
   
- SOURCES: 
    - [0]: https://docs.opencv.org/3.4.20/d2/d85/classcv_1_1StereoSGBM.html
    - [1]: https://stackoverflow.com/questions/65357601/how-a-good-depth-map-can-be-created-with-stereo-cameras inspo for param values
 
- NOTES:
 
*/

#include <iostream>
#include "opencv2/core.hpp"
#include <opencv2/calib3d.hpp> // needed for StereoSGBM 
#include <opencv2/highgui.hpp> // imshow, waitKey

int main(const int argc, const char * const argv[])
{
    if(argc < 3){
        std::cerr << "usage: " << argv[0] << "<path_to_left_image> <path_to_right_image>" << std::endl;
        return 1;
    }
    
    auto left = cv::imread(argv[1]);
    auto right = cv::imread(argv[2]);

    if(left.empty() || right.empty()){
        std::cerr << "ERROR: image not found..." << std::endl;        
        return 2;
    }

    const int minDisp = 0; // standard is 0, only not 0 if rectification shifted images
    const int numDisp = 64; // search range 0- 127 px. Must be div by 16
    const int blockSize = 11; // range 3-11, window comp. per pixl. Large = smooth but less details. 
    const int channels = 3; //BGR
    int penalty1 = 8 * channels * blockSize * blockSize; // formular from doc, penalty when neighbor disparity differs by 1
    int penalty2 = 32 * channels * blockSize * blockSize; // formular from doc, penalty when it differs by more then 1. This has to be larger then 2
    const int disp12MaxDiff = 1; // max allowed diff in the left-right disp check. to disable it set it to a non positive value
    const int preFilterCap = 1; // [AI-1] clipping of the pre filtered pixels. 
    const int uniquenessRatio = 15; // range 5-15, best match must beat the second best by x percent else its not valid
    const int speckleWindowSize = 75; // range 50-200, Regions smaller then this are treated as noise and removed. speckle is e.g noise
    const int speckleRange = 2; // according to doc, 1 or 2 is good enough. Disparity variation allowed inside a region (staubkörner auf bild)

    // [0] creates instance of StereoSGBM class
    auto stereoSGBMResult = cv::StereoSGBM::create(minDisp, numDisp, blockSize, penalty1, penalty2, disp12MaxDiff, preFilterCap, uniquenessRatio, speckleWindowSize, speckleRange);

    cv::Mat disp;
    stereoSGBMResult->compute(left, right, disp);

    cv::Mat disp8bit;
    disp.convertTo(disp8bit, CV_8U, 255.0 / (numDisp * 16));

    //cv::imshow("disparity", disp);
    cv::imshow("disparity 8 bit", disp8bit);
    cv::waitKey(0); 

    return 0;
}

