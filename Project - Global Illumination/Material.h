// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include "ColorDBL.h"


// TODO: Reference additional headers your program requires here.
class Material {

public:
	Material() : color(ColorDBL()), isReflective( false ), isLightSource( false ) {};

	Material(ColorDBL color_in, std::string materialType) : color(color_in) {
		if (materialType == "mirror") {
			isReflective = true;
		}
		else if (materialType == "light") {
			isLightSource = true;
		}
		else if (materialType == "lambertian") {
			isLambertian = true;
		}
	};

	ColorDBL getColor() const {
		return color;
	};

	ColorDBL changeColor(ColorDBL newColor) {
		color = newColor;
		return color;
	};

	bool checkIsReflective() const {
		return isReflective;
	};

	bool checkIsLightSource() const {
		return isLightSource;
	};

	bool checkIsLambertian() const {
		return isLambertian;
	};

private:
	ColorDBL color;
	bool isReflective = false;
	bool isLightSource = false;
	bool isLambertian = false;

};