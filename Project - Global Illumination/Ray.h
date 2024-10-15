// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "ColorDBL.h"
#include "Material.h"
#include "Light.h"
#include "Shape.h"
#include "Sphere.h"
#include <cmath>
#include <cstdlib>
#include <random>
#include <ctime>


// TODO: Reference additional headers your program requires here.
class Ray {

public:

	Ray* next;

	Ray(double i, double j, double delta) {
		srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
		ps = glm::vec3(-1.0, 0.0, 0.0); // Position of the eye
		glm::vec3 pe = glm::vec3(0.0, i * delta - (1.0 - delta), j * delta - (1.0 - delta)); // Position of the specific pixel
		rayDirection = glm::normalize(pe - ps);
		next = nullptr;
		collidedMaterial = nullptr;
	};

	Ray( glm::vec3 do_in, glm::vec3 ps_in ) {
		srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
		ps = ps_in;
		rayDirection = glm::normalize(do_in);
		next = nullptr;
		collidedMaterial = nullptr;
	}

	Ray reflection(Ray ray_in, glm::vec3 N, glm::vec3 intersectionPoint);

	Ray lambertianReflection(Ray ray_in, glm::vec3 N, Material surface_material, glm::vec3 intersectionPoint);

	glm::vec3 GetRayDirection() {
		return rayDirection;
	}

	glm::vec3 GetPs() {
			return ps;
	}

	void AddRayToList(Ray* newRay);

	ColorDBL GetLightIntensity(glm::vec3 normal, Light lightSource, int raysAmount, glm::vec3 intersectionPoint, std::vector<Shape*> shapes_in, std::vector<Sphere> spheres_in);

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

	int getPathLength() {
		return head->pathLength;
	}

	Ray* getPathStart() {
		return head;
	}

	Material* getCollidedMaterial() {
		return collidedMaterial;
	}

private:
	glm::vec3 ps; // Starting point of the ray
	glm::vec3 rayDirection; // Direction of the ray

	Ray* head = this;
	int pathLength = 0;

	Material* collidedMaterial;
};