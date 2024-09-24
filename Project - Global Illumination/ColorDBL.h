// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

class ColorDBL {
public:
	//Default contructor, RGB = (0,0,0) -> Svart
	ColorDBL() : r(0.0), g (0.0), b(0.0){};

	//Contructor to choose color
	ColorDBL(double red, double green, double blue) : r(red), g(green), b(blue) {};

	std::vector<double> getColor();





private:
	//Double precision values for colors
	double r;
	double g;
	double b;

};
// TODO: Reference additional headers your program requires here.
