// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Material.h"
#include "Rectangle.h"
#include <random>



class Light : public Rectangle {
public:

	Light(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, Material mat) {
		coordinates.push_back(point1);
		coordinates.push_back(point2);
		coordinates.push_back(point3);
		coordinates.push_back(point4);
		rectangleMaterial = mat;

		Area = glm::length(point2 - point1) * glm::length(point3 - point2);

		//normal = glm::normalize(glm::cross((point2 - point1), (point3 - point1)));
		normal = glm::normalize(glm::cross((point4 - point3), (point1 - point4)));
	};

	double GetArea() {
		return Area;
	}

	glm::vec3 ReturnE1() {

		glm::vec3 E1 = coordinates[1] - coordinates[0];

		return E1;
	}

	glm::vec3 ReturnE2() {
		glm::vec3 E2 = coordinates[2] - coordinates[1];

		return E2;
	}

	glm::vec3 RandomPointOnLight();


private:
	double Area;


	//double CalculateT(Ray ray_in) const;
};
// TODO: Reference additional headers your program requires here.
