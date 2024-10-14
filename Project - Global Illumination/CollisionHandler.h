// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "Material.h"
#include "Shape.h"
#include "Ray.h"
#include "Light.h"
#include "Scene.h"
#include "Sphere.h"


#include <iostream>
#include <vector>
#include <limits>

class CollisionHandler {
public:

	// Function that returns the material of the shape that a ray collides with
	static Material GetCollidingMaterial(std::vector<Shape*> shapes_in, Ray ray_in, Light lightSource, std::vector<Sphere> spheres_in) {
		glm::vec3 intersectionPoint = { 0, 0, 0 };
		glm::vec3 normal = { 0,0,0 };
		double distance = std::numeric_limits<double>::max();
		Material mat = Material();

		// Find the objects ("shape") that the ray collides with
		GetCollidingMaterialPolygon(shapes_in, ray_in, distance, intersectionPoint, mat, normal);
		GetCollidingMaterialSphere(spheres_in, ray_in, distance, intersectionPoint, mat, normal);

		// Apply lightning
		if(!mat.checkIsLightSource()) {
			ColorDBL intensity = ray_in.GetLightIntensity(normal, lightSource, 10, intersectionPoint, shapes_in, spheres_in);
			ColorDBL newColor = (mat.getColor()).MultiplyColor(intensity);
			mat.changeColor(newColor);
		}

		// Calculate the color within a mirror
		if (mat.checkIsReflective()) {

			mat = GetMirrorMaterial(shapes_in, ray_in, normal, intersectionPoint, lightSource, spheres_in);
			// ray_in.PrintRayPath();

		}

		return mat;
	}
private:

	static void GetCollidingMaterialPolygon(std::vector<Shape*> shapes_in, Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		// Find the objects ("shape") that the ray collides with
		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), rayDirection);
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(rayStartPos, rayDirection)) {
					glm::vec3 intersectionPoint = shape->GetIntersectionPoint(rayStartPos, rayDirection);
					// Find the object that is closest to the ray's starting position
					if (distance > glm::distance(rayStartPos, intersectionPoint)) {
						finalIntersectionPoint = intersectionPoint;
						distance = glm::distance(rayStartPos, intersectionPoint);
						mat = shape->GetMaterial();
						normal = shape->GetNormal();
					}
				}
			}
		}
	}

	static void GetCollidingMaterialSphere(std::vector<Sphere> spheres_in, Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		for (Sphere& sphere : spheres_in) {
			if (sphere.DoesCollide(rayDirection, rayStartPos)) {
				glm::vec3 intersectionPoint = sphere.GetIntersectionPoint(rayDirection, rayStartPos);
				// Find the object that is closest to the ray's starting position
				if (distance > glm::distance(rayStartPos, intersectionPoint)) {
					finalIntersectionPoint = intersectionPoint;
					distance = glm::distance(rayStartPos, intersectionPoint);
					mat = sphere.GetMaterial();
					normal = sphere.CalculateNormal(rayDirection, rayStartPos);
				}
			}
		}
	}

	// Function that returns the material of a ray within a mirror
	static Material GetMirrorMaterial(std::vector<Shape*> shapes_in, Ray& ray_in, glm::vec3 normal_in, glm::vec3 intersectionPoint_in, Light lightSource, std::vector<Sphere> spheres_in) {
		Ray ray = ray_in.reflection(ray_in, normal_in, intersectionPoint_in);
		Material mat = GetCollidingMaterial(shapes_in, ray, lightSource, spheres_in);
		return mat;
	}
};
// TODO: Reference additional headers your program requires here.
