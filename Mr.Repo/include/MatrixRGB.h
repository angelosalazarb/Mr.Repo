/**
 * @file ImagePGM.h
 * @author Ángelo Salazar, Juan José Revelo, Juan José Bailon (angelo.salazar, juan.jose.revelo, juan.bailon [@correounivalle.edu.co])
 * @version 0.1
 * @date 2020-10-27
 */
#ifndef MATRIXRGB_H_
#define MATRIXRGB_H_

/**--** Libraries **--**/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm> 

/* This class allows the user to create and 3 unidimensional vectors, representing Red, Green and Blue, similar to an NETPBM file */
class MatrixRGB {

  protected:
    unsigned int rows, cols, maxVal;
    std::vector <int> vectorHistogramaGrises;
    std::vector <int> vectorHistogramaRed;
    std::vector <int> vectorHistogramaGreen;
    std::vector <int> vectorHistogramaBlue;

    //vectors that stores R,G,B values
		std::vector< unsigned int > red;
		std::vector< unsigned int > green;
		std::vector< unsigned int > blue;

    std::string format; //Get the image type it could be P3 or P6
		std::string comment; // If it has a comment it will get it its represented by "#"

    /**
     * calculate the histogram values for the image pixels. (image in grayscale)
     * @contract <histogramaGrises><void> ---> <void>
     * 
     */
    void histogramaGrises(void);

    /**
     *  calculate the histogram values for the image pixels that 
     *  belong to the red channel
     * @contract <histogramRed><void> ---> <void>
     * 
     */
    void histogramRed(void);

    /**
     *  calculate the histogram values for the image pixels that 
     *  belong to the green channel
     * @contract <histogramGreen><void> ---> <void>
     * 
     */
    void histogramGreen(void);

    /**
     *  calculate the histogram values for the image pixels that 
     *  belong to the blue channel
     * @contract <histogramBlue><void> ---> <void>
     * 
     */
    void histogramBlue(void);

  public:

    /**
     * Construct a new MatrixRGB object
     * @contract <MatrixRGB><void> ---> <obj>
     * 
     */
    MatrixRGB();

    /**
     * Construct a new MatrixRGB object
     * @contract <MatrixRGB><int><int> ---> <obj>
     * @param int
     * @param int
     */
    MatrixRGB(unsigned int, unsigned int);

    /**
     * Construct a new MatrixRGB object
     * @contract <MatrixRGB><int><int><str> ---> <obj>
     * 
     * @param int 
     * @param int 
     * @param string
     **/
    MatrixRGB(unsigned int, unsigned int, std::string);

    /**
     * Construct a new MatrixRGB object
     * @contract <MatrixRGB><int><int><int><str> ---> <obj>
     *
     * @param int 
     * @param int 
     * @param int 
     * @param string
     **/
    MatrixRGB(unsigned int, unsigned int, unsigned int, std::string);

    /**
     * Destroy the MatrixRGB object
     * @contract <~MatrixRGB><obj> ---> <void>
     * 
     **/
    ~MatrixRGB();

    /**
     * This method multiplies a vector by a specific value
     * @contract <multiplyVectorBy><double><vector> ---> <void>
     * @param double has to be a positive number
     * @param vector
     **/
    void multiplyVectorBy(double, std::vector<unsigned int> &);

    /**
     * This method multiplies a vector by a specific value
     * @contract <multiplyVectorBy><double><vector> ---> <void>
     * @param double has to be a positive number
     * @param vector
     **/
    void multiplyVectorBy(double, std::vector<int> &);

    /**
     * This method makes the convolution between an 3x3 kernel and 
     * the image matrix, stores the resulst on the operotion in the given vector.
     * @contract <convolution><double array><vector> ---> <void>
     * 
     **/
    void convolution(double [3][3], std::vector<int> &, std::vector<int> &, std::vector<int> &);

    /**
     * This method reads an image from a specific file it could be PPM or PGM, even .txt
     * @contract <readImage><str> ---> <void>
     * 
     * @param filename 
     **/
    virtual void readImage(const std::string &filename) = 0;

    /**
     * This method writes an image in a specific file it could be PPM or PGM.
     * @contract <writeImage><str> ---> <void>
     * 
     * @param filename 
     **/
    virtual void writeImage(const std::string &filename) = 0;



};
#endif