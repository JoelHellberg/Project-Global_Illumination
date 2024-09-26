// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

class ColorDBL {
public:
	//Default contructor, RGB = (0,0,0) -> Black
	ColorDBL() : r(0.0), g (0.0), b(0.0){};

	//Contructor to choose color
	ColorDBL(double red, double green, double blue) : r(red), g(green), b(blue) {};

	std::vector<double> getColor() {

		return std::vector<double> {r, g, b};
	};

	static void displayColor(std::vector<double> n){

		std::cout << n[0] * 255.0 << " " << n[1] * 255.0 << " " << n[2] * 255.0 << "\n";

		// std::cout << n[0] << " " << n[1] << " " << n[2] << "\n";
		
			 
	}


private:
	//Double precision values for colors
	double r;
	double g;
	double b;

};
// TODO: Reference additional headers your program requires here.
