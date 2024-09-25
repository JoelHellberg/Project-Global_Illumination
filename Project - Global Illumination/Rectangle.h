// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "ColorDBL.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// TODO: Reference additional headers your program requires here.

class Rectangle {
public:
	Rectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, ColorDBL color_in) {
		coordinates.push_back(point1);
		coordinates.push_back(point2);
		coordinates.push_back(point3);
		coordinates.push_back(point4);
		color = color_in;

		//normal = glm::normalize(glm::cross((point2 - point1), (point3 - point1)));
		normal = glm::cross((point4 - point3), (point1 - point4));
	};
	glm::vec3 GetNormal() {
		return normal;
	}
	glm::vec3 GetV() {
		return coordinates[0];
	}
	glm::vec3 GetC1() {
		return coordinates[1] - coordinates[0];
	}
	glm::vec3 GetC2() {
		return coordinates[3] - coordinates[0];
	}
	ColorDBL FetchColor() {
		return color;
	}
	private:
		std::vector <glm::vec3> coordinates;
		ColorDBL color;
		glm::vec3 normal;
};

