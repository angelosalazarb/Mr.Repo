#include "../include/MatrixRGB.h"

#include <iostream>


MatrixRGB::MatrixRGB() 
  : rows(0), cols(0), maxVal(0), format(""), comment("")
  {}

MatrixRGB::MatrixRGB(unsigned int _rows, unsigned int _cols) 
  : rows(_rows), cols(_cols), maxVal(0), format(""), comment("")
  {}

MatrixRGB::MatrixRGB(unsigned int _rows, unsigned int _cols, std::string _format) 
  : rows(_rows), cols(_cols), maxVal(0), format(_format), comment("")
  {}

MatrixRGB::MatrixRGB(unsigned int _rows, unsigned int _cols, unsigned int _maxVal, std::string _format) 
  : rows(_rows), cols(_cols), maxVal(_maxVal), format(_format), comment("")
  {}

MatrixRGB::~MatrixRGB(){}


void MatrixRGB::multiplyVectorBy(double num, std::vector<unsigned int> &myvector){

  try{
    if(num<0) throw "El numero ingresado debe ser positivo";
  }catch(const char* e){
    std::cout<< e <<"\n";
  }

  for(int i=0; i<myvector.size(); i++){
    int temp = round(num * myvector[i]); 
    myvector[i] = temp;
  }

}


void MatrixRGB::multiplyVectorBy(double num, std::vector<int> &myvector){

  for(int i=0; i<myvector.size(); i++){
    int temp = round(num * myvector[i]); 
    myvector[i] = temp;
  }

}


void MatrixRGB::histogramaGrises(void){ //para hacer este histograma la imagen debe estar en grayscale
  vectorHistogramaGrises.resize(maxVal + 1);
  for(int i=0; i<vectorHistogramaGrises.size(); i++){
    vectorHistogramaGrises[i] = 0;
  }

  for(int i=0; i<red.size(); i++){
    int temp = red[i];
    vectorHistogramaGrises[temp] = vectorHistogramaGrises[temp] + 1; 
  } 

}

void MatrixRGB::histogramRed(void){ 

  vectorHistogramaRed.resize(maxVal + 1, 0);

  for(int i=0; i<red.size(); i++){
    int temp = red[i];
    vectorHistogramaRed[temp] = vectorHistogramaRed[temp] + 1; 
  } 
}

void MatrixRGB::histogramGreen(void){ 

  vectorHistogramaGreen.resize(maxVal + 1, 0);

  for(int i=0; i<green.size(); i++){
    int temp = green[i];
    vectorHistogramaGreen[temp] = vectorHistogramaGreen[temp] + 1; 
  } 
}

void MatrixRGB::histogramBlue(void){ 

  vectorHistogramaBlue.resize(maxVal + 1, 0);

  for(int i=0; i<blue.size(); i++){
    int temp = blue[i];
    vectorHistogramaBlue[temp] = vectorHistogramaBlue[temp] + 1; 
  } 
}



void MatrixRGB::convolution(double kernel[3][3], std::vector<int> &tempRed, std::vector<int> &tempGreen, std::vector<int> &tempBlue){

  double sumR=0, sumG=0, sumB=0;

  /**
   * if only if the image is in grayscale, then you could assign at least one value to
   * vectors enter as a paremeter tempGreen and tempBlue so that way the convolution 
   * process will be quiker, this is posible beuse the pixel values in red are gonna be
   * equal to the values in green and blue
   */
  if(tempRed.empty() && !tempGreen.empty() && !tempBlue.empty()){
    
    tempRed.resize(red.size(), 0);

    for(int i=1; i<rows-1; i++){
      for(int j=1; j<cols-1; j++){

          sumR = ( red[(cols*(i-1)) + j-1] * kernel[0][0] ) + ( red[(cols*(i-1)) + j] * kernel[0][1] ) + ( red[(cols*(i-1)) + j+1] * kernel[0][2] ) + ( red[(cols*i) + j-1] * kernel[1][0] ) + ( red[(cols*i) + j] * kernel[1][1] ) + ( red[(cols*i) + j+1] * kernel[1][2] ) + ( red[(cols*(i+1)) + j-1] * kernel[2][0] ) + ( red[(cols*(i+1)) + j] * kernel[2][1] ) + ( red[(cols*(i+1) + j+1)] * kernel[2][2] ) ;
  
          tempRed[(cols*i) + j] = int ( round(sumR) ) ; 

          sumR=0;         
      }
    }

  }
  // if the image is NOT grayscale then the three vectors enter as a paremeter
  // should be empty vectors
  else{
  
    tempRed.resize(red.size(), 0);
    tempGreen.resize(green.size(), 0);
    tempBlue.resize(blue.size(), 0);

    for(int i=1; i<rows-1; i++){
      for(int j=1; j<cols-1; j++){

            sumR = ( int(red[(cols*(i-1)) + j-1]) * kernel[0][0] ) + ( int(red[(cols*(i-1)) + j]) * kernel[0][1] ) + ( int(red[(cols*(i-1)) + j+1]) * kernel[0][2] ) + ( int(red[(cols*i) + j-1]) * kernel[1][0] ) + ( int(red[(cols*i) + j]) * kernel[1][1] ) + ( int(red[(cols*i) + j+1]) * kernel[1][2] ) + ( int(red[(cols*(i+1)) + j-1]) * kernel[2][0] ) + ( int(red[(cols*(i+1)) + j]) * kernel[2][1] ) + ( int(red[(cols*(i+1) + j+1)]) * kernel[2][2] ) ;
    
            tempRed[(cols*i) + j] = int ( round(sumR) ) ;

            sumG = ( green[(cols*(i-1)) + j-1] * kernel[0][0] ) + ( green[(cols*(i-1)) + j] * kernel[0][1] ) + ( green[(cols*(i-1)) + j+1] * kernel[0][2] ) + ( green[(cols*i) + j-1] * kernel[1][0] ) + ( green[(cols*i) + j] * kernel[1][1] ) + ( green[(cols*i) + j+1] * kernel[1][2] ) + ( green[(cols*(i+1)) + j-1] * kernel[2][0] ) + ( green[(cols*(i+1)) + j] * kernel[2][1] ) + ( green[(cols*(i+1) + j+1)] * kernel[2][2] ) ;
    
            tempGreen[(cols*i) + j] = int ( round(sumG) ) ;

            sumB = ( blue[(cols*(i-1)) + j-1] * kernel[0][0] ) + ( blue[(cols*(i-1)) + j] * kernel[0][1] ) + ( blue[(cols*(i-1)) + j+1] * kernel[0][2] ) + ( blue[(cols*i) + j-1] * kernel[1][0] ) + ( blue[(cols*i) + j] * kernel[1][1] ) + ( blue[(cols*i) + j+1] * kernel[1][2] ) + ( blue[(cols*(i+1)) + j-1] * kernel[2][0] ) + ( blue[(cols*(i+1)) + j] * kernel[2][1] ) + ( blue[(cols*(i+1) + j+1)] * kernel[2][2] ) ;
    
            tempBlue[(cols*i) + j] = int ( round(sumB) ) ;
            
            sumR=0; sumG=0; sumB=0;
      }
    }

  }
  
}

