// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "ColorDBL.h"
#include "Ray.h"

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

	ColorDBL FetchColor() {
		return color;
	}

	double CalculateT(glm::vec3 rayDirection);

	glm::vec3 GetIntersectionPoint(Ray ray_in);

	bool DoesCollide(Ray ray_in);

	private:

		std::vector <glm::vec3> coordinates;
		ColorDBL color;
		glm::vec3 normal;
};

