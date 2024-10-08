// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Sphere.h"
#include "Ray.h"
#include <cmath>


double Sphere::CalculateArg(glm::vec3 rayDirection, glm::vec3 center) const{
	glm::vec3 S(-1.0, 0.0, 0.0);
	glm::vec3 D = rayDirection;
	glm::vec3 C = center;

	double arg = 2.0f * glm::dot(D, (S - C));

	return arg;
}

void Sphere::CalculateC(glm::vec3 center, double radius, glm::vec3 rayDirection) {

	glm::vec3 S(-1.0, 0.0, 0.0);
	//D-Raydirection
	//C, spheres center
	//r, radius
	//Xc, surface point
	//S, eye(?)

	glm::vec3 D = rayDirection;
	glm::vec3 C = center;
	double r = radius;

	//c1 = D^2
	c1 = glm::dot(D, D); //D^2

	c2 = 2.0f * glm::dot(D, (S - C));

	//c2 = 2*D(S-C)

	//c3 = (S-C)^2 -r^2
	c3 = glm::dot((S - C), (S - C)) - std::pow(r,2);

	//t = (-c2 +- sqrt(c2^2 - 4*c1*c3))/(2*c1);
	//om c2^2-4*c1*c3 < 0 -> ray miss
	//om c2^2-4*c1*c3 = 0 -> ray touches sphere
	//om c2^2-4*c1*c3 > 0 -> ray touches sphere -> 2 solutions
}

float Sphere::CalculateT(glm::vec3 raydirection, glm::vec3 center) const{
		
	double arg = CalculateArg(raydirection, center);
	double t_min = 0;

	if (arg == 0) {
		t_min = -c2;
		return t_min;
	}
	else if(arg > 0) {
		 t_min = -c2 - sqrt(glm::dot(c2, c2) - 4 * glm::dot(c1, c3));
		return t_min;
	}
	else {
		return t_min;
	}
}


glm::vec3 Sphere::GetIntersectionPoint(glm::vec3 raydirection, glm::vec3 center) const {

	float t = CalculateT(raydirection, center);

	glm::vec3 Xr = center - raydirection * t;


	return Xr;
}


bool Sphere::DoesCollide(glm::vec3 ps, glm::vec3 rayDirection) const {

	return false;
}

