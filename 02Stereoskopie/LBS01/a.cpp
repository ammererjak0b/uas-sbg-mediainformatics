/*
- AUTHOR: Jakob Ammerer
- TASK: LBS01a)
- TODO: 
    Schreiben Sie ein Programm, dem ein linkes und ein rechtes Bild 
    vereinfacht als bereits rektifiziert angenommen) als Argumente ¨ubergeben werden,
    das aus beiden mit dem semiglobalen Stereo-Matcher (Klasse cv::StereoSGBM mit deren Methode compute)
    ein Disparit¨atsbild erzeugt. Verwenden Sie die in der OpenCV -Dokumentation empfohlenen Parameterwerte 
    (bzw. einen der Werte aus den empfohlenen Bereichen) und insgesamt 64 verschiedene Disparit¨aten.
    Geben Sie das Disparit¨atsbild abschlie- ßend in einem Fenster aus.
    Achten Sie dabei auf dessen korrekte Skalierung, d.h. konvertieren Sie das Tiefenbild mittels
    cv::Mat::convertTo in ein Graustufenbild, das 8 Bit Farbtiefe voll aussch¨opft 

    1. Einlesen, 2. Disp-Bild Erzeugen
- AI USAGE: Claude Sonnet 5.5
   
- SOURCES: 
 
- NOTES:
 
*/

#include <iostream>
#include "opencv2/core.hpp"
#include <opencv2/calib3d.hpp> // needed for StereoSGBM 

int main(const int argc, const char * const argv[])
{
    if(argc < 3){
        std::cerr "usage: " << argv[0] << "<path_to_left_image> <path_to_right_image>"
    }
    
    auto left = cv::Mat.imread(argv[1]);
    auto right = cv::Mat.imread(argv[2]);

    auto stereoResult = cv::StereoSGBM::create(
                

    );





    return 0;
}

