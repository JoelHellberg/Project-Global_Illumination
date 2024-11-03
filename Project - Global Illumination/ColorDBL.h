// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>


class ColorDBL {
public:
	//Default contructor, RGB = (0,0,0) -> Black
	ColorDBL() : r(0.0), g (0.0), b(0.0){};

	//Contructor to choose color
	ColorDBL(double red, double green, double blue) : r(red), g(green), b(blue) {};

	ColorDBL(glm::vec3 colors_in) : r(colors_in.x), g(colors_in.y), b(colors_in.z) {};

	std::vector<double> getColor() {

		return std::vector<double> {r, g, b};
	};

	glm::vec3 getColorGlm() {

		return glm::vec3(r, g, b);
	};

	static void displayColor(std::vector<double> n){

		std::cout << n[0] * 255.0 << " " << n[1] * 255.0 << " " << n[2] * 255.0 << "\n";
	}

	ColorDBL MultiplyColor(ColorDBL color1) {
		r *= color1.r;
		g *= color1.g;
		b *= color1.b;

		return *this;
	}

	ColorDBL AddColor(ColorDBL color1) {
		r += color1.r;
		g += color1.g;
		b += color1.b;

		return *this;
	}

	ColorDBL ClampColors() {
		r = std::clamp(r, 0.01, 1.0);
		g = std::clamp(g, 0.01, 1.0);
		b = std::clamp(b, 0.01, 1.0);

		return *this;
	}

	ColorDBL divide(double divider) const {
		if (divider <= 0) {
			return ColorDBL(1, 1, 1);
		}
		return ColorDBL(r / divider, g / divider, b / divider);
	}

	ColorDBL mult(double multiplier) const {
		return ColorDBL(r * multiplier, g * multiplier, b * multiplier);
	}

	ColorDBL& operator+=(const ColorDBL& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}


private:
	//Double precision values for colors
	double r;
	double g;
	double b;

};
// TODO: Reference additional headers your program requires here.
