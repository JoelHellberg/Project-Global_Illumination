// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "Triangle.cpp"
#include "Rectangle.cpp"


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

	double CalculateTRectangle(glm::vec3 surfaceNormal_in, glm::vec3 v_in) {
		// s: starting point (ps)
		// N: Normal of surface
		// D: direction of ray from eye
		// v: point of the surface(?)

		glm::vec3 v = v_in;
		glm::vec3 s = glm::vec3(-1.0, 0.0, 0.0);
		glm::vec3 N = surfaceNormal_in;
		glm::vec3 d = rayDirection;

		double t = glm::dot((v - s), N) / glm::dot(d, N);
		return t;
	}

	double CalculateTTriangle(Triangle triangle_in){

		std::vector<glm::vec3> coordinates = triangle_in.GetCoordinates();
		glm::vec3 T = ps - coordinates[0];
		glm::vec3 E_one = coordinates[1] - coordinates[0];
		glm::vec3 E_two = coordinates[2] - coordinates[0];
		glm::vec3 D = rayDirection;

		glm::vec3 P = glm::cross(D, E_two);
		glm::vec3 Q = glm::cross(T,E_one);

		double t = glm::dot(Q, E_two) / glm::dot(P, E_one);

		return t;

	}

	glm::vec3 GetIntersectionPointRectangle(Rectangle rectangle_in) {
		glm::vec3 surfaceNormal = rectangle_in.GetNormal();
		glm::vec3 v = rectangle_in.GetV();
		float t = CalculateTRectangle(surfaceNormal,v);

		return GetIntersectionPoint(surfaceNormal, v, t);
	}

	glm::vec3 GetIntersectionPointTriangle(Triangle triangle_in) {
		glm::vec3 surfaceNormal = triangle_in.GetNormal();
		glm::vec3 v = triangle_in.GetV();
		float t = CalculateTTriangle(triangle_in);

		return GetIntersectionPoint(surfaceNormal, v, t);
	}

	glm::vec3 GetIntersectionPoint(glm::vec3 surfaceNormal_in, glm::vec3 v_in, float t) {
		return ps + t * rayDirection;
	}

	bool DoesCollideRectangle(glm::vec3 surfaceNormal_in, glm::vec3 v_in, glm::vec3 c1, glm::vec3 c2) {
		float t = CalculateTRectangle(surfaceNormal_in, v_in);
		glm::vec3 xi = GetIntersectionPoint(surfaceNormal_in, v_in, t);
		double a = glm::dot((xi - v_in), c1) / glm::dot(c1, c1);
		double b = glm::dot((xi - v_in), c2) / glm::dot(c2, c2);

		return (0.0 <= a && a <= 1.0) && (0.0 <= b && b <= 1.0);

	}

	bool DoesCollideTriangle(Triangle triangle_in) {
		glm::vec3 v_in = triangle_in.GetV();
		glm::vec3 c1 = triangle_in.GetC1();
		glm::vec3 c2 = triangle_in.GetC2();
		float t = CalculateTTriangle(triangle_in);

		glm::vec3 xi = GetIntersectionPointTriangle(triangle_in);
		double a = glm::dot((xi - v_in), c1) / glm::dot(c1, c1);
		double b = glm::dot((xi - v_in), c2) / glm::dot(c2, c2);
		return (a >= 0.0 && b>=0.0) && (a+b<=1.0);
	}

private:
	glm::vec3 pe; // Position of the specific Pixel
	glm::vec3 ps; // Position of the eye
	glm::vec3 rayDirection; // Direction of the ray
};