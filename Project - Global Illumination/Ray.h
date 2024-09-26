// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <glm/glm.hpp>
#include <iostream>


// TODO: Reference additional headers your program requires here.
class Ray {

public:

	Ray(double i, double j, double delta) {
		ps = glm::vec3(-1.0, 0.0, 0.0);
		pe = glm::vec3(0.0, i * delta - (1.0 - delta), j * delta - (1.0 - delta));
		rayDirection = pe - ps;
	};

	glm::vec3 GetRayDirection() {
		return rayDirection;
	}

	glm::vec3 GetPs() {
		return ps;
	}

private:
	glm::vec3 pe; // Position of the specific Pixel
	glm::vec3 ps; // Position of the eye
	glm::vec3 rayDirection; // Direction of the ray
};