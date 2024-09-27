// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "ColorDBL.h"
#include "Material.h"



// TODO: Reference additional headers your program requires here.
class Ray {

public:

	Ray(double i, double j, double delta) {
		ps = glm::vec3(-1.0, 0.0, 0.0); // Position of the eye
		glm::vec3 pe = glm::vec3(0.0, i * delta - (1.0 - delta), j * delta - (1.0 - delta)); // Position of the specific pixel
		rayDirection = glm::normalize(pe - ps);
	};

	Ray( glm::vec3 do_in, glm::vec3 ps_in ) {
		ps = ps_in;
		rayDirection = glm::normalize(do_in);
	}

	Ray reflection(glm::vec3 di, glm::vec3 N, Material mat, glm::vec3 intersectionPoint);

	void reflect(glm::vec3 di, glm::vec3 N, Material mat, glm::vec3 intersectionPoint);


	glm::vec3 GetRayDirection() {
		return rayDirection;
	}

	glm::vec3 GetPs() {
			return ps;
	}

private:
	glm::vec3 ps; // Starting point of the ray
	glm::vec3 rayDirection; // Direction of the ray
};