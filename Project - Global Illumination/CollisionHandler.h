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
	// Function that returns the material the shape a ray collides with
	static Material GetCollidingMaterial(std::vector<Shape*> shapes_in, Ray ray_in) {
		bool shapeDetected = false;
		glm::vec3 intersectionPoint = { 0, 0, 0 };
		glm::vec3 normal = { 0, 0, 0 };
		Material mat = Material();

		// Find the specific object ("shape") that the ray collides with
		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), ray_in.GetRayDirection());
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(ray_in)) {
					mat = shape->GetMaterial();
					normal = shape->GetNormal();
					intersectionPoint = shape->GetIntersectionPoint(ray_in);
					shapeDetected = true;
					break;
				}
			}
		}

		// Calculate the color within a mirror
		if (mat.checkIsReflective() && shapeDetected) {

			Ray* ptr = &ray_in;
			mat = GetMirrorMaterial(shapes_in, ray_in, normal, intersectionPoint);

			while(true) {
				glm::vec3 direction = ptr->GetRayDirection();
				std::cout << "(" << direction.x << " , " << direction.y << " , " << direction.z << ")";

				if(ptr->next == nullptr) {
					std::cout << "\n";
					break;
				}
				else {
					ptr = ptr->next;
					std::cout << " --> ";
				}
			}
		}

		return mat;
	}
private:
	// Function that returns the material of a ray within a mirror
	static Material GetMirrorMaterial(std::vector<Shape*> shapes_in, Ray& ray_in, glm::vec3 normal_in, glm::vec3 intersectionPoint_in) {
		Ray ray = ray_in.reflection(ray_in, normal_in, intersectionPoint_in);
		Material mat = GetCollidingMaterial(shapes_in, ray);
		return mat;
	}
};
// TODO: Reference additional headers your program requires here.
