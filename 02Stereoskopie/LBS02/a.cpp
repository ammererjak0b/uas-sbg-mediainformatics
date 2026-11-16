#include <opencv2/core.hpp>
#include <iostream>
#include "CameraParameters.hpp"

/*
    Author: Jakob Ammerer
    TASK LBS02a)
    TODO: 
        read yaml-files (intrinsic, extrinisic) as arguments with cv::filestorage
        save in a fitting datastructure, be able to print, and reuse        
    Sources:
        see "CameraParamter.hpp"                

    AI-USAGE: Claude Sonnet 5.5
        see "CameraParameter.hpp"
 */

int main(const int argc, const char * const argv[]) {

    if(argc < 3){
        std::cerr << "usage: " << argv[0] << " <path_to_intrinsics_yml> <path_to_extrinsics_yml>" << std::endl;
        return 1;
    }

    CameraParameters parameters; 
    bool success = parameters.ReadCameraParameters(argv[1], argv[2]);

    if(!success){
        std::cerr << "ERROR: yml file not found..." << std::endl;
        return 2;
    }

    parameters.Print();

    return 0;
}






