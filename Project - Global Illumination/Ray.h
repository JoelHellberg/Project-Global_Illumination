// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <glm/glm.hpp>
#include <iostream>

// TODO: Reference additional headers your program requires here.
class Ray {
public:
	Ray(double i, double j, double delta) {
		pe = glm::vec3(0.0, i * delta - (delta - 1), j * delta - (delta - 1));
		ps = glm::vec3(-1.0, 0.0, 0.0);
		rayDirection = pe - ps;
	};
	glm::vec3 GetRayDirection() {
		return rayDirection;
	}
private:
	glm::vec3 pe; // Position of the specific Pixel
	glm::vec3 ps; // Position of the eye
	glm::vec3 rayDirection; // Direction of the ray
};