// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Rectangle.h"

double Rectangle::CalculateT(Ray ray_in) const {
	// s: starting point (ps)
	// N: Normal of surface
	// D: direction of ray from eye
	// v: point of the surface(?)

	glm::vec3 v = coordinates[0];
	glm::vec3 s = ray_in.GetPs();
	glm::vec3 N = normal;
	glm::vec3 d = ray_in.GetRayDirection();

	double t = glm::dot((v - s), N) / glm::dot(d, N);
	return t;
}

glm::vec3 Rectangle::GetIntersectionPoint(Ray ray_in) const {
	glm::vec3 rayDirection = ray_in.GetRayDirection();
	glm::vec3 ps = ray_in.GetPs();
	float t = CalculateT(ray_in);

	return ps + t * rayDirection;
}

bool Rectangle::DoesCollide(Ray ray_in) const {
	float t = CalculateT(ray_in);
	glm::vec3 xi = GetIntersectionPoint(ray_in);
	glm::vec3 v = coordinates[0];
	glm::vec3 c1 = coordinates[1] - coordinates[0];
	glm::vec3 c2 = coordinates[3] - coordinates[0];

	double a = glm::dot((xi - v), c1) / glm::dot(c1, c1);
	double b = glm::dot((xi - v), c2) / glm::dot(c2, c2);

	return (0.0 <= a && a <= 1.0) && (0.0 <= b && b <= 1.0);

}