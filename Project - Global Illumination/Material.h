// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include "ColorDBL.h"


// TODO: Reference additional headers your program requires here.
class Material {

public:
	Material() : color(ColorDBL()), isReflective( false ), isLightSource( false ) {};

	Material(ColorDBL color_in, bool isReflective_in) : color(color_in), isReflective(isReflective_in){};
	
	Material(ColorDBL color_in, bool isReflective_in, bool isLightSource_in) : color(color_in), isReflective(isReflective_in), isLightSource(isLightSource_in) {};

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

private:
	ColorDBL color;
	bool isReflective = false;
	bool isLightSource = false;

};