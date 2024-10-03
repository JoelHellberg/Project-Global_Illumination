// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <iostream>
#include "ColorDBL.h"
#include "Material.h"
#include "Light.h"
#include <cmath>



// TODO: Reference additional headers your program requires here.
class Ray {

public:

	Ray* next;

	Ray(double i, double j, double delta) {
		ps = glm::vec3(-1.0, 0.0, 0.0); // Position of the eye
		glm::vec3 pe = glm::vec3(0.0, i * delta - (1.0 - delta), j * delta - (1.0 - delta)); // Position of the specific pixel
		rayDirection = glm::normalize(pe - ps);
		next = nullptr;
	};

	Ray( glm::vec3 do_in, glm::vec3 ps_in ) {
		ps = ps_in;
		rayDirection = glm::normalize(do_in);
		next = nullptr;
	}

	Ray reflection(Ray ray_in, glm::vec3 N, glm::vec3 intersectionPoint);

	glm::vec3 GetRayDirection() {
		return rayDirection;
	}

	glm::vec3 GetPs() {
			return ps;
	}

	void AddRayToList(Ray* newRay);
	void AddToList(glm::vec3 newIntersectionPoint, Material mat);

	ColorDBL GetLightIntensity(Shape* shape, Light lightSource, int raysAmount);

	void PrintRayPath() {
		Ray* ptr = this;
		while (true) {
			glm::vec3 direction = ptr->GetRayDirection();
			std::cout << "(" << direction.x << " , " << direction.y << " , " << direction.z << ")";

			if (ptr->next == nullptr) {
				std::cout << "\n";
				break;
			}
			else {
				ptr = ptr->next;
				std::cout << " --> ";
			}
		}
	}

private:
	glm::vec3 ps; // Starting point of the ray
	glm::vec3 rayDirection; // Direction of the ray

	Ray* head = this;
};