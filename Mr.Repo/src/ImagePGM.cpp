#include "../include/ImagePGM.h"


ImagePGM::ImagePGM() {
  format = "P2";
}

ImagePGM::ImagePGM(const std::string &filename){
  fileName = filename;
  format = "P2";
  readImage(filename);

  green = red;
  blue = red;
}

ImagePGM::ImagePGM(const unsigned int width, const unsigned int height) 
  : ImagePPM(width, height)
  {
    format = "P3";
    red.reserve( width*height );
  }


ImagePGM::~ImagePGM(){}


void ImagePGM::readImage(const std::string &filename){

	std::ifstream infile;
	infile.open(filename.c_str(), std::ios::in );

	//check for error
	if(infile.fail()){
		std::cerr<<"Error opening file."<<std::endl;
		 exit(EXIT_FAILURE);
	}

	std::string temp;
	std::getline(infile, temp);

	if(temp!=format){
		std::cerr<<"Error file format is NOT "<< format <<std::endl;
		exit(EXIT_FAILURE);
	}

	std::getline(infile, comment);

	infile >> cols; //read colunms
	infile >> rows; //read rows

	infile >> maxVal; 

	
	red.reserve(rows*cols); 

	//read pixels values into the  RGB vectors, because is a PGM image
  //we're only gonna store pixel values in the red vector
	unsigned int aux;
	for(unsigned int i=0; i<rows*cols; ++i){

		infile>>aux;
		red.push_back(aux); 
	}

	if( rows*cols != red.size() ){
		std::cout<<"Could not read all the pixels on the file."<<std::endl;
	}else{
		std::cout<<"Everything is good, could read all the pixels on the image."<<std::endl;
	} 

	infile.close();

  //std::cout<< "leyendo PGM" <<"\n";

}


//write image pgm in the file
void ImagePGM::writeImage(const std::string &filename){

	std::ofstream file;
	file.open(filename.c_str(), std::ios::out);

	if( file.is_open() ){
		file << format <<"\n";
		file << "# Created by Mr.Repo\n";
		file << cols << " " << rows << "\n";
		file << maxVal << "\n";
	

		int j= 0;
		for(unsigned int i=0; i<rows*cols; i++){

			if(j>=0 && j<4){
				file << red[i]<<" ";
				j++;	
			}
			else{
				j=0;
				file << red[i]<<"\n";
			}	
					
		}
	}

	file.close();
  //std::cout<<"escribiendo PGM"<<"\n";
}
