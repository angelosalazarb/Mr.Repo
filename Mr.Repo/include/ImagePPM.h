/**
 * @file ImagePPM.h
 * @author Ángelo Salazar, Juan José Revelo, Juan José Bailon, (angelo.salazar, juan.jose.revelo, juan.bailon[@correounivalle.edu.co])
 * @version 0.1
 * @date 2020-10-27
 */

#ifndef IMAGEPPM_H_
#define IMAGEPPM_H_

#include <iostream>
#include <fstream>
#include "MatrixRGB.h"

class ImagePPM : public MatrixRGB {

  protected:
    std::string fileName;

  public:

    /**
     * Construct a new ImagePPM object
     * @contract <ImagePPM><void> ---> <obj>
     * 
     **/
    ImagePPM();

    /**
     * Construct a new ImagePPM object
     * @contract <ImagePPM><str> ---> <obj>
     * 
     * @param filename 
     **/
    ImagePPM(const std::string &filename);

    /**
     * Construct a new ImagePPM object
     * @contract <ImagePPM><int><int> ---> <obj>
     * 
     * @param width 
     * @param height 
     **/
    ImagePPM(const unsigned int width, const unsigned int height);

    /**
     * Destroy the Image PPM object
     * @contract <~ImagePPM><obj> ---> <void>
     * 
     **/
    ~ImagePPM();

    void readImage(const std::string &filename) override;

    void writeImage(const std::string &filename) override;
    
    /**
     * Apply the filter Black and white on our image.
     * @contract <grayScale><void> ---> <void>
     * 
     **/
    void grayScale(void);

    /**
     * Apply the sepia filter
     * @contract <sepia><void> ---> <void>
     * 
     **/
    void sepia(void);

    /**
     * This method do a vertical mirror in the image, using the vertical axis
     * @contract <flopped><void> ---> <void>
     * 
     **/
    void flopped(void);

    /**
     * This method do a horizontal mirror in the image, using the horizontal axis
     * @contract <flipped><void> ---> <void>
     * 
     **/
    void flipped(void);

    /**
     * This method calculates the histogram values of an specific color channel
     * @contract <flopped><void> ---> <void>
     * @param string this stsring is the name of one of the color channels.(red,green,blue,gray)
     **/
    void histogramPPM(std::string);
    
    /**
     * This method apply the threshold filter on the image
     * @contract <threshold><void> ---> <void>
     * 
     **/
    void threshold(void);

    /**
     * This method apply sobel filter on the  image. (edge detection)
     * @contract <sobel><void> ---> <void>
     * 
     **/
    void sobel(void);

    /**
     * This method make a composition between two images using a chromakey, the
     * image (ImagePPM) entered as a parameter must be the one with the chroma (green background)
     * @contract <flopped><ImagePPM> ---> <void>
     * 
     **/
    void chromaKey(ImagePPM &);

    /**
     * This method apply dilation on the image in a grade of intensity determine by num.
     * @contract <dilatation><void> ---> <void>
     * @param num num has to be a postive integer iqual or grater than 3.
     * num is the size of the square mask(matrix) that is gonna be use
     **/
    void dilation(int num=3);

    /**
     * This method apply erosion on the image in a grade of intensity determine by num.
     * @contract <dilatation><void><int> ---> <void>
     * @param num num has to be a postive integer iqual or grater than 3
     * num is the size of the square mask(matrix) that is gonna be use
     **/
    void erosion(int num=3);

    /**
     * This method assing color(pseudocolor) on the image
     * @contract <colorize><void> ---> <void>
     * 
     **/
    void colorize(void);
    
    /**
     * calculate disparity values ​​of image pixels, and stores then in the given vector
     * @contract <build_disparityMap><ImagePPM><vector> ---> <void>
     * 
     **/
    void build_disparityMap(ImagePPM &, std::vector<unsigned int> & disparityMap);

    /**
     * Gives a graphic representation fo the disparity between the two given images
     * @contract <disparityImage><ImagePPM> ---> <void>
     * @param imagePPM is the second photo(right picture)
     **/
    void disparityImage(ImagePPM &);

    /**
     * Gives a graphic representation of depth, determine the deepness of an object
     * in the image being represented by the intensity of the color. (Deeper = Darker)
     * @contract <depthPerceptionImage><ImagePPM> ---> <void>
     * @see build_disparityMap
     * @param ImagePPM is the second photo (right picture)
     **/
    void depthPerceptionImage(ImagePPM &);
    
    /**
     * This method apply mean blur to the image
     * @contract <meanBlur><void> ---> <void>
     * 
     **/
    void meanBlur(int intensityLevel=1);

    /**
     * enhances the edges of the image
     * @contract <sharpen><void> ---> <void>
     * 
     */
    void sharpen(void);

    /**
     * This method apply the negative filter on the image
     * @contract <negative><void> ---> <void>
     * 
     **/
    void negative(void);

};
#endif