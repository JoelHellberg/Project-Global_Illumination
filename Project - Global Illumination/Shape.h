// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Material.h"
#include "ColorDBL.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// TODO: Reference additional headers your program requires here.
class Shape {
public:

	virtual glm::vec3 GetNormal() const = 0;

	virtual ColorDBL FetchColor() const = 0;

	virtual Material GetMaterial() const = 0;

	virtual glm::vec3 GetIntersectionPoint(glm::vec3 ps, glm::vec3 rayDirection) const = 0;

	virtual bool DoesCollide(glm::vec3 ps, glm::vec3 rayDirection) const = 0;

	// Virtual destructor (recommended for base classes)
	virtual ~Shape() {
		// std::cout << "Shape destroyed\n";
	}
};