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
	double CalculateT(glm::vec3 surfaceNormal_in, glm::vec3 v_in) {
		// s: starting point (ps)
		// N: Normal of surface
		// D: direction of ray from eye
		// v: point of the surface(?)

		glm::vec3 v = v_in;
		glm::vec3 s = glm::vec3(-1, 0, 0);
		glm::vec3 N = surfaceNormal_in;
		glm::vec3 d = rayDirection;

		double t = glm::dot((v - s), N) / glm::dot(d, N);
		return t;
	}
	glm::vec3 GetIntersectionPoint(glm::vec3 surfaceNormal_in, glm::vec3 v_in) {
		float t = CalculateT(surfaceNormal_in, v_in);
		return ps + t * rayDirection;
	}
	bool DoesCollide(glm::vec3 surfaceNormal_in, glm::vec3 v_in, glm::vec3 c1, glm::vec3 c2) {
		glm::vec3 xi = GetIntersectionPoint(surfaceNormal_in, v_in);
		double a = glm::dot((xi - v_in), c1) / glm::dot(c1, c1);
		double b = glm::dot((xi - v_in), c2) / glm::dot(c2, c2);

		return (0 <= a && a <= 1) && (0 <= b && b <= 1);

	}
private:
	glm::vec3 pe; // Position of the specific Pixel
	glm::vec3 ps; // Position of the eye
	glm::vec3 rayDirection; // Direction of the ray
};