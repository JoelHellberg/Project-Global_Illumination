// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include "ColorDBL.h"


// TODO: Reference additional headers your program requires here.
class Material {

public:
	Material() : color(ColorDBL()), luminance(ColorDBL(1.0,1.0,1.0)), isReflective( false ), isLightSource( false ) {};

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
		else if (materialType == "metallic") {
			isMetallic = true;
		}
	};

	ColorDBL getColor() const {
		return color;
	};

	ColorDBL changeColor(ColorDBL newColor) {
		color = newColor;
		return color;
	};

	ColorDBL getLuminance() const {
		return luminance;
	};

	ColorDBL changeLuminance(ColorDBL newLuminance) {
		luminance = newLuminance;
		return luminance;
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

	bool checkIsMetallic() const {
		return isMetallic;
	};

private:
	ColorDBL color;
	ColorDBL luminance;
	bool isReflective = false;
	bool isLightSource = false;
	bool isLambertian = false;
	bool isMetallic = false;

};