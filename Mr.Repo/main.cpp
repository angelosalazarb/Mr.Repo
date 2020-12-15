#include <iostream>
#include "include/MatrixRGB.h"
#include "include/ImagePPM.h"
#include "include/ImagePGM.h"
#include <vector>

int main () {

  ImagePPM i1("../Mr.Repo/images/lenna_PPM.ppm"); //image_disparity_left
  //ImagePPM i2("../proyecto juan/images/image_disparity_right.ppm"); //image_disparity_right
  //ImagePGM i3("../proyecto juan/images/lenna_PGM.pgm");
    std::cout<<"\n";
    
    //i1.dilation(5);
    //i1.erosion();
    //i1.sobel();
    i1.meanBlur(17);
    //i1.sharpen();
    //i1.chromaKey(i2);
    //i1.threshold();
    //i1.pseudocolor();
    //i1.disparityImage(i2);
    //i1.depthPerceptionImage(i2);
    //i1.grayScale();
    //i1.histogramPPM("green");
    i1.writeImage("../Mr.Repo/images/cuadroX.ppm");    

  return 0;
}