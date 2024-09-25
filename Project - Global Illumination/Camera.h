// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "Ray.cpp"
#include <iostream>

// TODO: Reference additional headers your program requires here.
class Camera {
public:
	Camera(double width, double height) {
		delta = 1.0 / (width / 2.0); // Funkar bara om width = height, bör ändras
	};

	Ray GetRay(double i, double j) {
		Ray dummy_ray = Ray(i, j, delta);
		return dummy_ray;
	}

	glm::vec3 GetRayDirection(double i, double j) {
		Ray dummy_ray = Ray(i, j, delta);
		return dummy_ray.GetRayDirection();
	}
private:
	glm::vec3 eye = glm::vec3(-1.0, 0.0, 0.0);
	glm::vec3 cameraCenter = glm::vec3(0.0, 0.0, 0.0);
	double delta;
};