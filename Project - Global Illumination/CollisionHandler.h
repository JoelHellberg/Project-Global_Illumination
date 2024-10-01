// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "Material.h"
#include "Shape.h"
#include "Ray.h"

#include <iostream>
#include <vector>

class CollisionHandler {
public:
	//Default contructor, RGB = (0,0,0) -> Black

	static Material GetCollidingMaterial(std::vector<Shape*> shapes_in, Ray ray) {
		bool shapeDetected = false;
		glm::vec3 intersectionPoint = { 0, 0, 0 };
		glm::vec3 normal = { 0, 0, 0 };
		Material mat = Material();

		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), ray.GetRayDirection());
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(ray)) {
					mat = shape->GetMaterial();
					normal = shape->GetNormal();
					intersectionPoint = shape->GetIntersectionPoint(ray);
					shapeDetected = true;
					break;
				}
			}
		}

		if (mat.checkIsReflective() && shapeDetected) {
			ray = ray.reflection(ray.GetRayDirection(), normal, mat, intersectionPoint);
			mat = GetCollidingMaterial(shapes_in, ray);
		}
		return mat;
	}

};
// TODO: Reference additional headers your program requires here.
