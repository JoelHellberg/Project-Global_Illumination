// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Shape.h"

// TODO: Reference additional headers your program requires here.

class Rectangle : public Shape {
public:

	Rectangle() : rectangleMaterial(Material()), normal({ 0,0,0 }) {}

	Rectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, Material mat) {
		coordinates.push_back(point1);
		coordinates.push_back(point2);
		coordinates.push_back(point3);
		coordinates.push_back(point4);
		rectangleMaterial = mat;

		//normal = glm::normalize(glm::cross((point2 - point1), (point3 - point1)));
		normal = glm::normalize(glm::cross((point4 - point3), (point1 - point4)));
	};

	glm::vec3 GetNormal() const override {
		return normal;
	}

	ColorDBL FetchColor() const override {
		return rectangleMaterial.getColor();
	}

	Material GetMaterial() const override {
		return rectangleMaterial;
	}

	glm::vec3 GetIntersectionPoint(glm::vec3 ps, glm::vec3 rayDirection) const override;

	bool DoesCollide(glm::vec3 ps, glm::vec3 rayDirection) const override;

protected:
	std::vector <glm::vec3> coordinates;
	Material rectangleMaterial;
	glm::vec3 normal;

	double CalculateT(glm::vec3 ps, glm::vec3 rayDirection) const;
};

