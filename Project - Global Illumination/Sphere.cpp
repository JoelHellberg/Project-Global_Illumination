// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Sphere.h"


void Sphere::CalculateNormal(glm::vec3 Xr, glm::vec3 center) {
	 
	normal = (Xr - center) / glm::length(Xr - center);

}

//void Sphere::CalculateC(glm::vec3 center, double radius, glm::vec3 rayDirection) {
//
//	glm::vec3 S(-1.0, 0.0, 0.0);
//	//D-Raydirection
//	//C, spheres center
//	//r, radius
//	//Xc, surface point
//	//S, eye(?)
//
//	glm::vec3 D = rayDirection;
//	glm::vec3 C = center;
//	double r = radius;
//
//	//c1 = D^2
//	c1 = glm::dot(D, D); //D^2
//
//	c2 = 2.0f * glm::dot(D, (S - C));
//
//	//c2 = 2*D(S-C)
//
//	//c3 = (S-C)^2 -r^2
//	c3 = glm::dot((S - C), (S - C)) - std::pow(r, 2);
//
//	//t = (-c2 +- sqrt(c2^2 - 4*c1*c3))/(2*c1);
//	//om c2^2-4*c1*c3 < 0 -> ray miss
//	//om c2^2-4*c1*c3 = 0 -> ray touches sphere
//	//om c2^2-4*c1*c3 > 0 -> ray touches sphere -> 2 solutions
//}

double Sphere::CalculateArg(glm::vec3 rayDirection, glm::vec3 center) {
	glm::vec3 S(-1.0, 0.0, 0.0);
	glm::vec3 D = rayDirection;
	glm::vec3 C = center;

	c1 = glm::dot(D, D);
	c2 = 2.0f * glm::dot(D, S - C);
	c3 = glm::dot(S - C, S - C);

	double arg = std::pow(c2, 2.0) - 4.0 * c1 * c3;

	return arg;
}



glm::vec3 Sphere::GetIntersectionPoint(glm::vec3 raydirection) {



	double arg = CalculateArg(raydirection, center);

	float t_min = 0.0;

	if (arg == 0.0) {
		t_min = -c2 / 2.0 * c1;
	}
	else if (arg > 0) {
		t_min = (-c2 - sqrt(glm::dot(c2, c2) - 4.0 * glm::dot(c1, c3))) / (2.0 * c1);
	}

	
	glm::vec3 Xr = center - raydirection * t_min;


	return Xr;
}

bool Sphere::DoesCollide(glm::vec3 raydirection) {

	double arg = CalculateArg(raydirection, center);


	if (arg == 0.0) {
		return true;
	}
	else if (arg > 0.0) {
		return true;
	}
	else {
		return false;
	}
}

