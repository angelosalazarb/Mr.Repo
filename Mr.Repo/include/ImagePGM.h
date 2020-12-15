/**
 * @file ImagePGM.h
 * @author Ángelo Salazar, Juan José Revelo, Juan José Bailon (angelo.salazar, juan.jose.revelo, juan.bailon [@correounivalle.edu.co])
 * @version 0.1
 * @date 2020-10-27
 */

#ifndef IMAGEPGM_H_
#define IMAGEPGM_H_

#include <iostream>
#include <fstream>
#include "ImagePPM.h"


class ImagePGM : public ImagePPM {

  public:

    /**
     * Construct a new ImagePGM object
     * @contract <ImagePGM><void> ---> <obj>
     * 
     */
    ImagePGM();
    /**
     * Construct a new ImagePGM object
     * @contract <ImagePGM><string> ---> <obj>
     * 
     */
    ImagePGM(const std::string &filename);
    /**
     * Construct a new ImagePGM object
     * @contract <ImagePGM><unsigned int><unsigned int> ---> <obj>
     * 
     */
    ImagePGM(const unsigned int width, const unsigned int height);
   
    /**
     * Destroy the ImagePGM object
     * @contract <~ImagePGM><void> ---> <obj>
     * 
     */
    ~ImagePGM();

    void readImage(const std::string &filename) override;

    void writeImage(const std::string &filename) override;

};



#endif