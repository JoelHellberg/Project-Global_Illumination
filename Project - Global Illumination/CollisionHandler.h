// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define _USE_MATH_DEFINES
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

	CollisionHandler(std::vector<Shape*> room_in, std::vector<Shape*> obstacles_in, std::vector<Sphere> spheres_in, Light lightSource, double noSamples_in, int maxDepth_in)
	: scene_shapes(room_in), scene_obstacles(obstacles_in), scene_spheres(spheres_in), scene_lightsource(lightSource), noSamples(noSamples_in), maxDepth(maxDepth_in){
		for (Shape* obstacle : obstacles_in) {
			scene_shapes.push_back(obstacle);
		}
	}

	// Function that returns the material of the shape that a ray collides with
	Material GetCollidingMaterial(Ray ray_in) {
		glm::vec3 intersectionPoint = { 0, 0, 0 };
		glm::vec3 normal = { 0,0,0 };
		double distance = std::numeric_limits<double>::max();
		Material mat = Material();

		// Find the objects ("shape") that the ray collides with
		int objectId = 0;
		GetCollidingMaterialPolygon(ray_in, distance, intersectionPoint, mat, normal, objectId);
		GetCollidingMaterialSphere(ray_in, distance, intersectionPoint, mat, normal, objectId);

		// Apply lightning
		if(!mat.checkIsLightSource()) {
			ColorDBL intensity = ray_in.GetLightIntensity(normal, scene_lightsource, 5, intersectionPoint, scene_obstacles, scene_spheres, objectId);
			mat.changeLuminance(intensity);
			ColorDBL newColor = (mat.getColor() * intensity).ClampColors();
			mat.changeColor(newColor);
		}

		// Calculate the color within a mirror
		if (mat.checkIsReflective()) {
			Ray ray = ray_in.reflection(ray_in, normal, intersectionPoint);
			Material newMat = GetCollidingMaterial(ray);
			mat.changeColor(newMat.getColor() * 0.8);
			// ray_in.PrintRayPath();
		}

		 // Calculate the color of a Lambertian material
		if (mat.checkIsLambertian() || mat.checkIsMetallic()) {

			double albedo = 0.8;
			constexpr double bsrdf = 0.8 / glm::pi<float>();

			double absorptionChance = 0.2;
			float randomFactor = static_cast<float>(rand()) / RAND_MAX;

			// Nuvarande mechanic så att en ray studsar MAX 5 gånger
			if (randomFactor > absorptionChance && ray_in.getPathLength() <= maxDepth) {
					Ray ray = ray_in.lambertianReflection(ray_in, normal, intersectionPoint);

					double cosOmega = glm::dot(normal, ray.GetRayDirection()) / (glm::length(normal) * glm::length(ray.GetRayDirection()));
					ColorDBL reflectiveColor(0.0, 0.0, 0.0);
					for (int i = 0; i < noSamples; i++) {
						Material newMat = GetCollidingMaterial(ray);
						reflectiveColor += newMat.getColor() * bsrdf * cosOmega;  // Accumulate the color
					}
					// Average the colors after the loop
					// reflectiveColor = reflectiveColor / noSamples;

					ColorDBL newColor = mat.getColor() + reflectiveColor;
					mat.changeColor(newColor);
			}
			else {
				mat.changeColor(mat.getColor());
			}
		}

		if (mat.checkIsMetallic()) {
			Ray ray = ray_in.reflection(ray_in, normal, intersectionPoint);
			Material newMat = GetCollidingMaterial(ray);
			ColorDBL reflectedColor = newMat.getColor();  // Color from the reflection

			ColorDBL baseColor = mat.getColor();  // Base color of the metal
			// Use metallicFactor to blend between base color and reflection
			float metallicFactor = 0.8;  // Degree of metallic appearance
			ColorDBL newColor = baseColor * (1.0f - metallicFactor) + reflectedColor * metallicFactor;

			mat.changeColor(newColor);
		}

		return mat;
	}
private:
	std::vector<Shape*> scene_shapes;
	std::vector<Shape*> scene_obstacles;
	std::vector<Sphere> scene_spheres;
	Light scene_lightsource;
	double noSamples;
	int maxDepth;

	void GetCollidingMaterialPolygon(Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal, int& objectId) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		// Find the objects ("shape") that the ray collides with
		for (Shape* shape : scene_shapes) {
			double dotProduct = glm::dot(shape->GetNormal(), rayDirection);
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(rayStartPos, rayDirection)) {
					glm::vec3 intersectionPoint = shape->GetIntersectionPoint(rayStartPos, rayDirection);
					// Find the object that is closest to the ray's starting position
					if (distance > glm::distance(rayStartPos, intersectionPoint)) {
						finalIntersectionPoint = intersectionPoint;
						distance = glm::distance(rayStartPos, intersectionPoint);
						objectId = shape->getShapeID();
						mat = shape->GetMaterial();
						normal = shape->GetNormal();
					}
				}
			}
		}
	}

	void GetCollidingMaterialSphere(Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal, int& objectId) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		for (Sphere& sphere : scene_spheres) {
			if (sphere.DoesCollide(rayDirection, rayStartPos)) {
				glm::vec3 intersectionPoint = sphere.GetIntersectionPoint(rayDirection, rayStartPos);
				// Find the object that is closest to the ray's starting position
				if (distance > glm::distance(rayStartPos, intersectionPoint)) {
					finalIntersectionPoint = intersectionPoint;
					distance = glm::distance(rayStartPos, intersectionPoint);
					objectId = sphere.getShapeID();
					mat = sphere.GetMaterial();
					normal = sphere.CalculateNormal(rayDirection, rayStartPos);
				}
			}
		}
	}

	// Function that returns the material of a ray within a mirror
	//Material GetMirrorMaterial(std::vector<Shape*> shapes_in, Ray& ray_in, glm::vec3 normal_in, glm::vec3 intersectionPoint_in, Light lightSource, std::vector<Sphere> spheres_in) {
	//	Ray ray = ray_in.reflection(ray_in, normal_in, intersectionPoint_in);
	//	Material mat = GetCollidingMaterial(ray, );
	//	return mat;
	//}
};
// TODO: Reference additional headers your program requires here.
