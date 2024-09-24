// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "ColorDBL.cpp"
#include <iostream>

// TODO: Reference additional headers your program requires here.

class Rectangle {
public:
	glm::vec3 coordinates[4];
	Rectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, ColorDBL color) {
		coordinates[0] = point1;
		coordinates[1] = point2;
		coordinates[2] = point3;
		coordinates[3] = point4;
	};
	private:
};

