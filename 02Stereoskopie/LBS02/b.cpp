/*
- AUTHOR: Jakob Ammerer
- TASK: LBS02b)
- TODO: 
    Extend Application LBS01b), 2 additional arguments (ymls)
    read yml via CameraParameter.hpp, rectify both images with these values.
    Show rectified images for testing and calculate disparity.
    
- AI USAGE: Claude Sonnet 5.5
    - See LBS01b)
    - See "CameraParameter.hpp"
    - [AI-1]: Used Ai to explain in easy terms what the function "initUndistortRectifyMap" does. 
- SOURCES: 
    - See LBS01b)
    - See "CameraParameter.hpp"
    - [0]: https://docs.opencv.org/3.4.20/d9/d0c/group__calib3d.html#ga617b1685d4059c6040827800e72ad2b6
    - [1]: https://docs.opencv.org/3.4.20/da/d54/group__imgproc__transform.html#ga7dfb72c9cf9780a347fbe3d1c47e5d5a
    - [2]: https://docs.opencv.org/3.4.20/da/d54/group__imgproc__transform.html#gab75ef31ce5cdfb5c44b6da5f3b908ea4
    - [3]: https://docs.opencv.org/4.13.0/da/d54/group__imgproc__transform.html#gga5bb5a1fea74ea38e1a5445ca803ff121ac97d8e4880d8b5d509e96825c7522deb interpolation. Link to this page of the interpolation types provided by Leon Angerer

*/

#include <iostream>
#include "opencv2/core.hpp"
#include <opencv2/calib3d.hpp> // needed for StereoSGBM 
#include <opencv2/highgui.hpp> // imshow, waitKey
#include "CameraParameters.hpp"
#include <opencv2/imgproc.hpp> // remap

int main(const int argc, const char * const argv[])
{
    if(argc < 5){
        std::cerr << "usage: " << argv[0] << " <left_image> <right_image> <intrinsics_yml> <extrinsics_yml>" << std::endl;
        return 1;
    }
    
    CameraParameters parameters; 
    bool success = parameters.ReadCameraParameters(argv[3], argv[4]);

    if(!success){
        std::cerr << "ERROR: yml file not found..." << std::endl;
        return 2;
    }

    auto left = cv::imread(argv[1]);
    auto right = cv::imread(argv[2]);

    if(left.empty() || right.empty()){
        std::cerr << "ERROR: image not found..." << std::endl;        
        return 2;
    }

    // [0]: stereo Rectify: Wie muss jede Cam virtuell gedreht werden, damit beide Bildebenen in einer Ebene sind (Epipolorlinien horizontal ausrichten) berechnet also die Drehung.<  
    cv::Mat rectifyLeft;
    cv::Mat rectifyRight;
    cv::Mat projectionLeft;
    cv::Mat projectionRight; 
    cv::Mat disparityToDepth;

    cv::stereoRectify(
        parameters.intrinsicCameraMatrixLeft,
        parameters.intrinsicDistortionLeft,
        parameters.intrinsicCameraMatrixRight,
        parameters.intrinsicDistortionRight,
        left.size(), 
        parameters.extrinsicRotation,
        parameters.extrinsicTranslation,
        rectifyLeft,
        rectifyRight,
        projectionLeft,
        projectionRight,
        disparityToDepth
    );

    // [1] creates search Table per camera called map. foreach px in the finished picture there is now a verweis to the px position in the original picture (x, y)... [AI-2] more in docs
    cv::Mat mapLeft1, mapLeft2, mapRight1, mapRight2; // map1 = x values, map2 = y values
    cv::initUndistortRectifyMap(parameters.intrinsicCameraMatrixLeft, parameters.intrinsicDistortionLeft, rectifyLeft, projectionLeft, left.size(), CV_32FC1, mapLeft1, mapLeft2);
    cv::initUndistortRectifyMap(parameters.intrinsicCameraMatrixRight, parameters.intrinsicDistortionRight, rectifyRight, projectionRight, right.size(), CV_32FC1, mapRight1, mapRight2);

    // [2] remap applies the search table map from aboce to the image
    cv::Mat leftRectified, rightRectified;
    cv::remap(left, leftRectified, mapLeft1, mapLeft2, cv::INTER_LINEAR); //  [3] bilinear interpolation type provided by Leon Angerer
    cv::remap(right, rightRectified, mapRight1, mapRight2, cv::INTER_LINEAR);

    cv::imshow("left rectified", leftRectified); // shown at the final waitKey
    cv::imshow("right rectified", rightRectified);

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
    
    auto stereoSGBMResult = cv::StereoSGBM::create(minDisp, numDisp, blockSize, penalty1, penalty2, disp12MaxDiff, preFilterCap, uniquenessRatio, speckleWindowSize, speckleRange);

    cv::Mat disp;
    stereoSGBMResult->compute(leftRectified, rightRectified, disp);

    cv::Mat disp8bit;
    disp.convertTo(disp8bit, CV_8U, 255.0 / (numDisp * 16));

    //cv::imshow("disparity", disp);
    cv::imshow("disparity 8 bit", disp8bit);
    cv::waitKey(0); 

    return 0;
}

