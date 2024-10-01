// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Ray.h"

// TODO: Reference additional headers your program requires here.
class Shape {
public:

	virtual glm::vec3 GetNormal() const = 0;

	virtual ColorDBL FetchColor() const = 0;

	virtual Material GetMaterial() const = 0;

	virtual double CalculateT(Ray ray_in) const = 0;

	virtual glm::vec3 GetIntersectionPoint(Ray ray_in) const = 0;

	virtual bool DoesCollide(Ray ray_in) const = 0;

	// Virtual destructor (recommended for base classes)
	virtual ~Shape() {
		// std::cout << "Shape destroyed\n";
	}
};