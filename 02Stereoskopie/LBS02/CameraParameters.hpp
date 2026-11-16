#pragma once // header guard, file is only included once per .cpp
#include <iostream>
#include <string>
#include "opencv2/core.hpp" 

/*
    INFO: I know the header is only to declare the functions a class uses.
          I only implemented the functions in the header, because our makefile makes a .exe out of every cpp file
          and I did not wanna bother with the Makefile template. [AI-0]
    SOURCES: 
        - [0] https://docs.opencv.org/5.0/main_modules/classcv_1_1FileStorage.html
        - [1] https://softwareengineering.stackexchange.com/questions/419427/when-to-ever-use-separate-implementation-files-cpp-files-in-modern-c
        - [2] VO-Slides

    AI-USAGE: Claude Sonnet 5.5
        - [AI-0]: Asked about a workaround for the original .cpp to be not made into a exe without touching the template makefile. Claude recommended this approach. 
                  Which I found out is not that good cause it increases compile time according to this: [1]
                  But in this case only tasks a), b), c) are using this header file and i take that increased compile time for the convinience of reusing the code easily with the same Makefile. 
        
        - [AI-1]: Discussed with Claude
    */

// this class combines both matrices (extrinsic and intrinsic) of both yaml files. 
class CameraParameters {
public:
    // intrinsics.yml
    cv::Mat intrinsicCameraMatrixLeft; // M1: 3x3, focal length + principal point, left camera
    cv::Mat intrinsicDistortionLeft; // D1: 1x12, lens distortion left
    cv::Mat intrinsicCameraMatrixRight; // M2 
    cv::Mat intrinsicDistortionRight; // D2

    // extrinsics.yml
    cv::Mat extrinsicRotation; // R: 3x3, rotation right camera to left camera
    cv::Mat extrinsicTranslation; // T: 3x1, shift right camera to left camera
    cv::Mat extrinsicRectifyLeft; // R1: 3x3, rotation to make image planes coplanar, left
    cv::Mat extrinsicRectifyRight; // R2
    cv::Mat extrinsicProjectionLeft; // P1: 3x4, new camera matrix after rectification, left
    cv::Mat extrinsicProjectionRight; // P2
    cv::Mat extrinsicDisparityToDepth; // Q: 4x4, disparity to 3-D point (needed in task c)

    // reads both yml files into this object, returns false if one cannot be opened
    bool ReadCameraParameters(const std::string intrinsicsPath, const std::string extrinsicsPath)
    {
        cv::FileStorage intrinsicsFile(intrinsicsPath, cv::FileStorage::READ); // open yml for reading
        cv::FileStorage extrinsicsFile(extrinsicsPath, cv::FileStorage::READ);

        if(!intrinsicsFile.isOpened() || !extrinsicsFile.isOpened()){ // missing file = no exception, only false
            return false;
        }

        // file["name"] = node with this name (same as XmlNode Object in C#), .mat() converts a node to cv::Mat obj.
        intrinsicCameraMatrixLeft = intrinsicsFile["M1"].mat();
        intrinsicDistortionLeft = intrinsicsFile["D1"].mat();
        intrinsicCameraMatrixRight = intrinsicsFile["M2"].mat();
        intrinsicDistortionRight = intrinsicsFile["D2"].mat();

        extrinsicRotation = extrinsicsFile["R"].mat();
        extrinsicTranslation = extrinsicsFile["T"].mat();
        extrinsicRectifyLeft = extrinsicsFile["R1"].mat();
        extrinsicRectifyRight = extrinsicsFile["R2"].mat();
        extrinsicProjectionLeft = extrinsicsFile["P1"].mat();
        extrinsicProjectionRight = extrinsicsFile["P2"].mat();
        extrinsicDisparityToDepth = extrinsicsFile["Q"].mat();

        return true; 
    }

    void Print() 
    {
        std::cout << "Intrinsic parameters" << std::endl;
        PrintMatrix("M1", intrinsicCameraMatrixLeft);
        PrintMatrix("D1", intrinsicDistortionLeft);
        PrintMatrix("M2", intrinsicCameraMatrixRight);
        PrintMatrix("D2", intrinsicDistortionRight);

        std::cout << "Extrinsic parameters" << std::endl;
        PrintMatrix("R",  extrinsicRotation);
        PrintMatrix("T",  extrinsicTranslation);
        PrintMatrix("R1", extrinsicRectifyLeft);
        PrintMatrix("R2", extrinsicRectifyRight);
        PrintMatrix("P1", extrinsicProjectionLeft);
        PrintMatrix("P2", extrinsicProjectionRight);
        PrintMatrix("Q",  extrinsicDisparityToDepth);
    }

private:
    // prints name, size (rows x cols) and the matrix, one blank line after
    // this style of formatting for the print was taken from Leon Angerer, it is a "prettier" style of console output
    void PrintMatrix(const std::string& name, const cv::Mat& matrix)
    {
        std::cout << name << " (" << matrix.rows << "x" << matrix.cols << "):\n"
                  << matrix << "\n\n";
    }
};
