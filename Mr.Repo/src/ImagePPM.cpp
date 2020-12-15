#include "../include/ImagePPM.h"

ImagePPM::ImagePPM()
  : fileName("")
 {
  format = "P3";
  maxVal = 255;
 }

ImagePPM::ImagePPM(const std::string &filename) 
  : fileName(filename) 
  {
	maxVal=255;
	format= "P3";
	readImage(filename);
  }

ImagePPM::ImagePPM(const unsigned int width, const unsigned int height) 
  : MatrixRGB(height, width, 255, "P3") , fileName("")
  {
	red.reserve( width*height );
	green.reserve( width*height );
	blue.reserve( width*height );
  }

ImagePPM::~ImagePPM(){}


void ImagePPM::readImage(const std::string &filename){

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

	infile >> maxVal; //read intensity max value

	
	red.reserve(rows*cols);
	green.reserve(rows*cols);
	blue.reserve(rows*cols);  

	//read RGB values into the  RGB vectors
	unsigned int aux;
	for(unsigned int i=0; i<rows*cols*3; ++i){

		infile>>aux;
		red.push_back(aux);
		i++;
		infile>>aux;
		green.push_back(aux);
		i++;
		infile>>aux;
		blue.push_back(aux); 
	}

	if(rows*cols != red.size() || rows*cols != green.size() || rows*cols != blue.size()){
		std::cout<<"Could not read all the pixels on the file."<<std::endl;
	}else{
		std::cout<<"Everything is good, could read all the pixels on the image."/*<<std::endl*/;
	} 

	infile.close();

}


//write image ppm in the file
void ImagePPM::writeImage(const std::string &filename){

	std::ofstream file;
	file.open(filename.c_str(), std::ios::out);

	if( file.is_open() ){
		file << format <<"\n";
		file << "# Created by Mr.Repo\n";
		file << cols << " " << rows << "\n";
		file << maxVal << "\n";
	//}

		int j= 0;
		for(unsigned int i=0; i<rows*cols; i++){

			if(j>=0 && j<4){
				file << red[i]<<" "<<green[i]<<" "<<blue[i]<<" ";
				j++;	
			}
			else{
				j=0;
				file << red[i]<<" "<<green[i]<<" "<<blue[i]<<"\n";
			}	
					
		}
	}

	file.close();

}


void ImagePPM::grayScale(void){

  multiplyVectorBy(0.299, red);
  multiplyVectorBy(0.587, green);
  multiplyVectorBy(0.114, blue);

  for(int i=0; i<red.size(); i++){
    unsigned int temp = red[i]+green[i]+blue[i];
    red[i]= temp;
    green[i]= temp;
    blue[i]= temp;
  }
}


void ImagePPM::sepia(void){

  for(int i=0; i<red.size(); i++){
    int tr = round( 0.393*red[i] + 0.769*green[i] + 0.189*blue[i] );
    int tg = round( 0.349*red[i] + 0.686*green[i] + 0.168*blue[i] );
    int tb = round( 0.272*red[i] + 0.534*green[i] + 0.131*blue[i] );

    unsigned int r = (tr>255) ? 255 : tr;
    unsigned int g = (tg>255) ? 255 : tg;
    unsigned int b = (tb>255) ? 255 : tb;

    red[i]= r;
    green[i]= g;
    blue[i]= b;
  }
}



void ImagePPM::flopped(void){

  std::vector<unsigned int> tempRed;
	std::vector<unsigned int> tempGreen;
	std::vector<unsigned int> tempBlue;

	tempRed.reserve( red.size() );
	tempGreen.reserve( green.size()) ;
	tempBlue.reserve( blue.size() );


	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){

			// here we invert the positions of the columns
			// example: last column in red will be the first column in tempRed
			tempRed.push_back( red[ (cols*(i+1)) - 1 - j ] );
			tempGreen.push_back( green[ (cols*(i+1)) - 1 - j ] );
			tempBlue.push_back( blue[ (cols*(i+1)) - 1 - j ] );

		}
	}

	for(int i=0; i<red.size(); i++){
		red[i] = tempRed[i];
		green[i] = tempGreen[i];
		blue[i] = tempBlue[i];
	}

}




void ImagePPM::flipped(void){

  std::vector<unsigned int> tempRed;
	std::vector<unsigned int> tempGreen;
	std::vector<unsigned int> tempBlue;

	tempRed.reserve( red.size() );
	tempGreen.reserve( green.size()) ;
	tempBlue.reserve( blue.size() );


	for(int i=rows; i>0; i--){
		for(int j=0; j<cols; j++){

			// here we invert the positions of the rows
			// example: last row in red will be the first row in tempRed
			tempRed.push_back( red[ (cols*(i-1)) + j ] );
			tempGreen.push_back( green[ (cols*(i-1)) + j ] );
			tempBlue.push_back( blue[ (cols*(i-1)) + j ] );

		}
	}

	for(int i=0; i<red.size(); i++){
		red[i] = tempRed[i];
		green[i] = tempGreen[i];
		blue[i] = tempBlue[i];
	}

}


void ImagePPM::histogramPPM(std::string chanel){

	if(chanel == "gray" || chanel == "Gray"){
		grayScale();
		histogramaGrises();
		for(int i=0; i<vectorHistogramaGrises.size(); i++){
			std::cout<< i <<": " << vectorHistogramaGrises[i] <<" ; ";
		}
	}
	else if(chanel == "red" || chanel == "Red"){
		histogramRed();
		for(int i=0; i<vectorHistogramaRed.size(); i++){
			std::cout<< i <<": " << vectorHistogramaRed[i] <<" ; ";
		}
	}
	else if(chanel == "green" || chanel == "Green"){
		histogramGreen();
		for(int i=0; i<vectorHistogramaGreen.size(); i++){
			std::cout<< i <<": " << vectorHistogramaGreen[i] <<" ; ";
		}
	}
	else if(chanel == "blue" || chanel == "Blue"){
		histogramBlue();
		for(int i=0; i<vectorHistogramaBlue.size(); i++){
			std::cout<< i <<": " << vectorHistogramaBlue[i] <<" ; ";
		}
	}
	else{
		std::cout<< "Please type a correct chanel. (red, green, blue, gray) " <<"\n";
	}

}


//to undertand this method check info about "thresholding" and "ISODATA algorithm"
void ImagePPM::threshold(void){

	if(vectorHistogramaGrises.empty()){
		grayScale();
		histogramaGrises();
	}

	double miu1, miu2, numerador =0, demominador =0;
	bool flag = true;
	double T_i = 127, T_f = 0, thresholdValue=0;

	while (flag)
	{

		for(int i=0; i<=T_i; i++){
		numerador += i * int(vectorHistogramaGrises[i]);
		demominador += int(vectorHistogramaGrises[i]);
		}

		miu1 = numerador/demominador;
	
		numerador=0; demominador=0;
		for(int i=T_i; i<=255; i++){
			numerador += i * int(vectorHistogramaGrises[i]);
			demominador += int(vectorHistogramaGrises[i]);
		}
		
		miu2 = numerador/demominador;

		double T = (miu1+miu2)*0.5;  	

		T_f = T;
		if(T_i == T_f){
			thresholdValue = round( T_f );
			flag = false;
		}else{
			T_i = T;
		}

	}


	for(int i=0; i<red.size(); i++){
		if( red[i] < thresholdValue ){
			red[i] = 0;
		}
		else if(red[i] >= thresholdValue){
			red[i] = 255;
		}
	}

	green = red;
	blue = red;

}

//check info about "sobel filter" and "image convolution"
void ImagePPM::sobel(void){

	grayScale();

	double g_x[3][3] = { {0.125, 0, -0.125},
											 {0.25, 0, -0.25},
											 {0.125, 0, -0.125}
										};

	double g_y[3][3] = { {0.125, 0.25, 0.125},
											 {0, 0, 0},
											 {-0.125, -0.25, -0.125}
										};		

	std::vector<int> salida_x;
	std::vector<int> salida_y;	

	std::vector<int> v(1, -1);							

	// to see why we pass v that way as a parameter, go check the 
	// method convolution on MatrixRGB.cpp
	convolution(g_x, salida_x, v, v);
	convolution(g_y, salida_y, v, v);

	std::vector<unsigned int> salida_final; 
	salida_final.resize(red.size());

	for(int i=0; i<salida_x.size(); i++){
		salida_final[i] = int( round( sqrt( pow(salida_x[i], 2) + pow(salida_y[i], 2) ) ) ) ; 
	}
	
	red = salida_final;
	green = salida_final;
	blue = salida_final;
	//std::cout<< "salida size: "<<salida_x.size() <<"\n ";

}


void ImagePPM::chromaKey(ImagePPM &other){

	try{
		if(other.rows > rows  ||  other.cols > cols){
			throw "The image is too big";
		}
	}catch(const char* e){
		std::cout<< e <<"\n";
	}

	//chroma Red,Green and Blue; are the average of RGB the values that belong
	// to the chromaKey image (the green background)
	int chromaRed = round( ( other.red[0] + other.red[1] + other.red[other.cols] + other.red[other.cols - 1] + other.red[other.cols - 2] + other.red[(2*other.cols) - 1] + other.red[(other.rows - 1)*other.cols] + other.red[(other.rows - 1)*other.cols + 1] ) / 8.0 );

	int chromaGreen = round( ( other.green[0] + other.green[1] + other.green[other.cols] + other.green[other.cols - 1] + other.green[other.cols - 2] + other.green[(2*other.cols) - 1] + other.green[(other.rows - 1)*other.cols] + other.green[(other.rows - 1)*other.cols + 1] ) / 8.0 );

	int chromaBlue = round( ( other.blue[0] + other.blue[1] + other.blue[other.cols] + other.blue[other.cols - 1] + other.blue[other.cols - 2] + other.blue[(2*other.cols) - 1] + other.blue[(other.rows - 1)*other.cols] + other.blue[(other.rows - 1)*other.cols + 1] ) / 8.0 );


	// this indicates where in the backgroung image is gonna be the starting
	// row and column of the image with the chromakey
	int foregroundBegin_row = floor( (( 1 -  other.rows/double(rows))/2.0) * rows ) ;
	int foregroundBegin_col = floor( (( 1 -  other.cols/double(cols))/2.0) * cols ) ;
	

	//this for loop determines with pixel in image (image with the green backgroung) are of
	// of the chromakey (the background). Then assigns then the most pure green color possible (0, 255, 0).
	for(int i=0; i<other.red.size(); i++){
		
		if( (chromaGreen - 10) <= int(other.green[i])  &&  int(other.green[i]) <= (chromaGreen + 10) ){

			if( (chromaBlue - 10) <= int(other.blue[i])  &&  int(other.blue[i]) <= (chromaBlue + 10) ){
				
				if( (chromaRed - 10) <= int(other.red[i])  &&  int(other.red[i]) <= (chromaRed + 10) ){
					other.red[i] = 0;
					other.green[i] = 255;
					other.blue[i] = 0;
				}
			}			
		}

	}   
	
	std::vector<unsigned int> tempRed ( red.size() );
	std::vector<unsigned int> tempGreen ( green.size() );
	std::vector<unsigned int> tempBlue ( blue.size() );

	tempRed = red;
	tempGreen = green;
	tempBlue = blue;

	//this for loop insert in front of the backgroung image the foreground image.
	// foreground image = the chroma key image (including the green backgroung) 
	int contador=0;
	for(int i=foregroundBegin_row; i < (foregroundBegin_row + other.rows); i++){
		for(int j=foregroundBegin_col; j < (foregroundBegin_col + other.cols); j++){

			red[(cols*i) + j] = other.red[contador];
			green[(cols*i) + j] = other.green[contador];
			blue[(cols*i) + j] = other.blue[contador];

			contador++;
				
			}
		}


	// this for loop searh for pixels that belong to the chroma key and then
	// replace them with their corresponding pixel of the backgroung image	
	for(int i=0; i<red.size(); i++){
		
		if( int(green[i]) == 255 ){

			if( int(blue[i]) == 0 ){
				
				if( int(red[i]) == 0 ){

					red[i] = tempRed[i];
					green[i] = tempGreen[i];
					blue[i] = tempBlue[i];
				}
			}			
		}

	}
	
	
}



void ImagePPM::dilation(int num){

	try{
		if(3>num){
			throw "The input number has to be greater than 3";
		}else if(num%2 == 0){
			throw "The input number has to be an odd number";
		}
		else if(num < 0){
			throw "The input number has to be a posite integer";
		}
		else if(cols<=num || rows<=num){
			throw "The input number is too big";
		}

	}catch(const char* e){
		std::cout<< e <<"\n";
		exit(EXIT_FAILURE);
	}


	threshold();

	/** 
	 * mask is the num x num matrix, wich is going to be using to compare
	 * a specific grid of values with the rest of the image */ 
	int maskCenterRow = floor( num/2.0 );
	int maskCenterCol = floor( num/2.0 );

	std::vector<unsigned int> tempRed (red.size());
	std::vector<unsigned int> tempGreen (green.size());
	std::vector<unsigned int> tempBlue (blue.size());

	tempRed = red;
	tempGreen = green;
	tempBlue = blue;


	for(int i= maskCenterRow; i<(rows-maskCenterRow); i++){
		for(int j= maskCenterCol; j<(cols-maskCenterCol); j++){

			if( red[(cols*i) + j] == 255 ){

				for(int k=i-maskCenterRow; k<(i-maskCenterRow)+num; k++){
					for(int l=j-maskCenterCol; l<(j-maskCenterCol)+num; l++){

						tempRed[(cols*k)+l] = 255;
						tempGreen[(cols*k)+l] = 255;
						tempBlue[(cols*k)+l] = 255;

					}
				}
			}

		}
	}

	red.clear();
	green.clear();
	blue.clear();

	red = tempRed;
	green = tempGreen;
	blue = tempBlue;

}


void ImagePPM::erosion(int num){

	try{
		if(3>num){
			throw "The input number has to be greater than 3";
		}else if(num%2 == 0){
			throw "The input number has to be an odd number";
		}
		else if(num < 0){
			throw "The input number has to be a posite integer";
		}
		else if(cols<=num || rows<=num){
			throw "The input number is too big";
		}

	}catch(const char* e){
		std::cout<< e <<"\n";
		exit(EXIT_FAILURE);
	}


	threshold();

	/** 
	 * mask is the num x num matrix, wich is going to be using to compare
	 * a specific grid of values with the rest of the image */
	int maskCenterRow = floor( num/2.0 );
	int maskCenterCol = floor( num/2.0 );

	std::vector<unsigned int> tempRed (red.size(), 0);
	std::vector<unsigned int> tempGreen (green.size(), 0);
	std::vector<unsigned int> tempBlue (blue.size(), 0);
	
	tempRed = red;
	tempGreen = green;
	tempBlue = blue; 


	for(int i= maskCenterRow; i<(rows-maskCenterRow); i++){
		for(int j= maskCenterCol; j<(cols-maskCenterCol); j++){

			if( red[(cols*i) + j] == 0 ){

				for(int k=i-maskCenterRow; k<(i-maskCenterRow)+num; k++){
					for(int l=j-maskCenterCol; l<(j-maskCenterCol)+num; l++){
							
							tempRed[(cols*k)+l] = 0;
							tempGreen[(cols*k)+l] = 0;
							tempBlue[(cols*k)+l] = 0;
											

					}
				}
			}

		}
	}

	red.clear();
	green.clear();
	blue.clear();

	red = tempRed;
	green = tempGreen;
	blue = tempBlue;

}



void ImagePPM::colorize(void){

	/**
	 * the image has to be converter into grayscale so that 
	 * way we can assing of the false color to the image  
	*/
	grayScale();

	int max=0, min=255;
	for(int i=0; i<red.size(); i++){ //finds the min ans max intensities
		if(red[i] > max)
			max = red[i];
		if(red[i] < min)
			min = red[i];
	}

	// to understand this below part check "intensity slicing"
	// this is the method use to assing the pseudocolor
	int planeDistance, planes[14]; 
	planeDistance = round( (max-min)/13.0 );   	


	planes[0]=min; 
	planes[14-1]=max;
	for(int i=1; i<13; i++){
		planes[i] = planes[i-1] + planeDistance;
	}
	

	for(int i=0; i<red.size(); i++){

		if( planes[0] <= red[i] && red[i] < planes[1] ){
			red[i] = 148;
			green[i] = 0;
			blue[i] = 211;
		}
		else if( planes[1] <= red[i] && red[i] < planes[2] ){
			red[i] = 75;
			green[i] = 0;
			blue[i] = 130;
		}
		else if( planes[2] <= red[i] && red[i] < planes[3] ){
			red[i] = 38;
			green[i] = 0;
			blue[i] = 193;
		}
		else if( planes[3] <= red[i] && red[i] < planes[4] ){
			red[i] = 0;
			green[i] = 0;
			blue[i] = 255;
		}
		else if( planes[4] <= red[i] && red[i] < planes[5] ){
			red[i] = 9;
			green[i] = 80;
			blue[i] = 247;
		}
		else if( planes[5] <= red[i] && red[i] < planes[6] ){
			red[i] = 9;
			green[i] = 247;
			blue[i] = 235;
		}
		else if( planes[6] <= red[i] && red[i] < planes[7] ){
			red[i] = 0;
			green[i] = 255;
			blue[i] = 0;
		}
		else if( planes[7] <= red[i] && red[i] < planes[8] ){
			red[i] = 127;
			green[i] = 255;
			blue[i] = 0;
		}
		else if( planes[8] <= red[i] && red[i] < planes[9] ){
			red[i] = 255;
			green[i] = 255;
			blue[i] = 0;
		}
		else if( planes[9] <= red[i] && red[i] < planes[10] ){
			red[i] = 255;
			green[i] = 191;
			blue[i] = 0;
		}
		else if( planes[10] <= red[i] && red[i] < planes[11] ){
			red[i] = 255;
			green[i] = 127;
			blue[i] = 0;
		}
		else if( planes[11] <= red[i] && red[i] < planes[12] ){
			red[i] = 255;
			green[i] = 68;
			blue[i] = 0;
		}
		else if( planes[12] <= red[i] && red[i] < planes[13] ){
			red[i] = 255;
			green[i] = 0;
			blue[i] = 0;
		}
		
	}


}


//to undertand this method check info about "stereo image disparity" and "SAD (sum of absolute differences)"
void ImagePPM::build_disparityMap(ImagePPM & rightImage, std::vector<unsigned int> & disparityMap){

	try{
		if(rows != rightImage.rows || cols != rightImage.cols)
			throw "The two images should have the same size";

	}catch(const char* e){
		std::cout<< e <<"\n";
		exit(EXIT_FAILURE);
	}


	int sum=0;
	int kernel[3][3];
	std::vector <int> SAD_vector;

	if( !disparityMap.empty() ){
		disparityMap.clear();
		disparityMap.resize(red.size(), 0);
	}else{
		disparityMap.resize(red.size(), 0);
	}


	for(int i=1; i<rows-1; i++){
		for(int j=1; j<cols-1; j++){

			kernel[0][0] = red[(cols*(i-1)) + j-1];
			kernel[0][1] = red[(cols*(i-1)) + j];
			kernel[0][2] = red[(cols*(i-1)) + j+1];
			kernel[1][0] = red[(cols*i) + j-1];
			kernel[1][1] = red[(cols*i) + j];
			kernel[1][2] = red[(cols*i) + j+1];
			kernel[2][0] = red[(cols*(i+1)) + j-1];
			kernel[2][1] = red[(cols*(i+1)) + j];
			kernel[2][2] = red[(cols*(i+1) + j+1)];


			for(int k=1; k<rightImage.cols-1; k++){
				using namespace std;

				sum = abs( kernel[0][0] - int(rightImage.red[(cols*(i-1)) + k-1]) ) + abs( kernel[0][1] - int(red[(cols*(i-1)) + k]) ) + abs( kernel[0][2] - int(red[(cols*(i-1)) + k+1]) ) + abs( kernel[1][0] - int(red[(cols*i) + k-1]) ) + abs( kernel[1][1] - int(red[(cols*i) + k]) ) + abs( kernel[1][2] - int(red[(cols*i) + k+1]) ) + abs( kernel[2][0] - int(red[(cols*(i+1)) + k-1]) ) + abs( kernel[2][1] - int(red[(cols*(i+1)) + k]) ) + abs( kernel[2][2] - int(red[(cols*(i+1) + k+1)]) ) ;

				SAD_vector.push_back(sum);
				sum=0;
			}
			

			int min_difference = *std::min_element( SAD_vector.begin(), SAD_vector.end() );

			auto it = find(SAD_vector.begin(), SAD_vector.end(), min_difference);

			int x_L = j;
			int x_R = ( it - SAD_vector.begin() +1);

			int disparity =  std::abs( x_L - x_R ) ;
			disparity = (disparity>255)? 255 : disparity;

			disparityMap[(cols*i) + j] =  disparity;

			SAD_vector.clear();
		}
	}

}



void ImagePPM::disparityImage(ImagePPM & rightImage){

	std::vector <unsigned int> disparityMap;

	build_disparityMap(rightImage, disparityMap);

	red = disparityMap;
	green = disparityMap;
	blue = disparityMap;

}


//to undertand this method check info about "binocular disparity", "depth on stereo images" and "depth map from stereo images"
void ImagePPM::depthPerceptionImage(ImagePPM & rightImage){

	std::vector <unsigned int> disparityMap;

	build_disparityMap(rightImage, disparityMap);

	int min_disparity = *std::min_element( disparityMap.begin(), disparityMap.end() );
	int max_disparity = *std::max_element( disparityMap.begin(), disparityMap.end() );
	int range = max_disparity - min_disparity;

	int planes[256], planeDistance;
	planeDistance = round(range/254.0);

	planes[0]=min_disparity; 
	planes[256-1]=max_disparity;
	for(int i=1; i<256-1; i++){
		planes[i] = planes[i-1] + planeDistance;
	}

	int colors[256];
	for(int i=0; i<256; i++){
		colors[i] = i;
	}


	for(int i=0; i<disparityMap.size(); i++){
		for(int j=0; j<256-1; j++){
				
			if(disparityMap[i] == max_disparity){
				red[i] = 255;
			}
			if(disparityMap[i] == min_disparity){
				red[i] = 0;
			}
			if(planes[j] < disparityMap[i]  &&  disparityMap[i] < planes[j+1]){
				red[i] = colors[j];
			}
		}
	}

	green=red;
	blue=red;

}


void ImagePPM::negative(void){

    for(int i = 0; i < red.size(); i++){

        red[i] = maxVal - red[i];
        green[i] = maxVal - green[i];
        blue[i] = maxVal - blue[i];
    }
}


//to undertand this method check info about "mean blur filter" and "image convolution"
void ImagePPM::meanBlur(int  intensityLevel){

	double kernel[3][3] = { {1,1,1},
													{1,1,1},
													{1,1,1}
				 							  };

	for(int i=0; i<intensityLevel; i++){
		std::vector <int> tempRed;
		std::vector <int> tempGreen;
		std::vector <int> tempBlue;

		convolution(kernel, tempRed, tempGreen, tempBlue);

		double num = (1.0/9.0);

		multiplyVectorBy(num, tempRed);
		multiplyVectorBy(num, tempGreen);
		multiplyVectorBy(num, tempBlue);

		for (int i=0; i<red.size(); i++){
			red[i] = tempRed[i];
			green[i] = tempGreen[i];
			blue[i] = tempBlue[i];
		}

	}

}


//to undertand this method check info about "sharpen filter" and "image convolution"
void ImagePPM::sharpen(void){

	double kernel[3][3] = { {0,-1,0},
													{-1,5,-1},
													{0,-1,0}
				 							  };

		std::vector <int> tempRed;
		std::vector <int> tempGreen;
		std::vector <int> tempBlue;

		convolution(kernel, tempRed, tempGreen, tempBlue);

		for (int i=0; i<red.size(); i++){
			red[i] = int( std::abs( tempRed[i] ) );
			green[i] = int( std::abs( tempGreen[i] ) );
			blue[i] = int( std::abs( tempBlue[i] ) );
		}
											 
}
