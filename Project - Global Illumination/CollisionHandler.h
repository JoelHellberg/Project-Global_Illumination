// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "Material.h"
#include "Shape.h"
#include "Ray.h"
#include "Light.h"

#include <iostream>
#include <vector>
#include <limits>

class CollisionHandler {
public:
	// Function that returns the material of the shape that a ray collides with
	static Material GetCollidingMaterial(std::vector<Shape*> shapes_in, Ray ray_in, Light lightSource) {
		bool shapeDetected = false;

		glm::vec3 finalIntersectionPoint = { 0, 0, 0 };
		glm::vec3 normal = { 0,0,0 };
		double distance = std::numeric_limits<double>::max();
		Material mat = Material();

		// Find the objects ("shape") that the ray collides with
		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), ray_in.GetRayDirection());
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(ray_in.GetPs(), ray_in.GetRayDirection())) {
					glm::vec3 intersectionPoint = shape->GetIntersectionPoint(ray_in.GetPs(), ray_in.GetRayDirection());
					glm::vec3 rayStartPoint = ray_in.GetPs();
					// Find the object that is closest to the ray's starting position
					if (distance > glm::distance(rayStartPoint, intersectionPoint)) {
						finalIntersectionPoint = intersectionPoint;
						distance = glm::distance(rayStartPoint, intersectionPoint);
						mat = shape->GetMaterial();
						normal = shape->GetNormal();
					}
					shapeDetected = true;
				}
			}
		}

		//Apply lightning
		ColorDBL intensity = ray_in.GetLightIntensity(normal, lightSource, 5, finalIntersectionPoint);
		ColorDBL newColor = (mat.getColor()).MultiplyColor(intensity);
		mat.changeColor(newColor);

		// Calculate the color within a mirror
		if (mat.checkIsReflective() && shapeDetected) {

			mat = GetMirrorMaterial(shapes_in, ray_in, normal, finalIntersectionPoint, lightSource);
			// ray_in.PrintRayPath();

		}

		return mat;
	}
private:
	// Function that returns the material of a ray within a mirror
	static Material GetMirrorMaterial(std::vector<Shape*> shapes_in, Ray& ray_in, glm::vec3 normal_in, glm::vec3 intersectionPoint_in, Light lightSource) {
		Ray ray = ray_in.reflection(ray_in, normal_in, intersectionPoint_in);
		Material mat = GetCollidingMaterial(shapes_in, ray, lightSource);
		return mat;
	}
};
// TODO: Reference additional headers your program requires here.
