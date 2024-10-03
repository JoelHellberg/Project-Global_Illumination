// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Shape.h"

class Triangle : public Shape {
public:
	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, Material mat) {
		coordinates.push_back(point1); //Coordniates[0]
		coordinates.push_back(point2); //Coordinates[1]
		coordinates.push_back(point3); //Cordinates[2]
		triangleMat = mat;

		normal = glm::normalize(glm::cross((point1 - point3), (point2 - point1)));
	};

	glm::vec3 GetNormal() const override {
		return normal;
	}

	ColorDBL FetchColor() const override {
		return triangleMat.getColor();
	}

	Material GetMaterial() const override {
		return triangleMat;
	}

	glm::vec3 GetIntersectionPoint(glm::vec3 ps, glm::vec3 rayDirection) const override;

	bool DoesCollide(glm::vec3 ps, glm::vec3 rayDirection) const override;

private:
	std::vector <glm::vec3> coordinates;
	Material triangleMat;
	glm::vec3 normal;

	double CalculateT(glm::vec3 ps, glm::vec3 rayDirection) const;
};
