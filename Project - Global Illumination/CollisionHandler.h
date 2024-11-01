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

	CollisionHandler(std::vector<Shape*> room_in, std::vector<Shape*> obstacles_in, std::vector<Sphere> spheres_in, Light lightSource)
	: scene_shapes(room_in), scene_obstacles(obstacles_in), scene_spheres(spheres_in), scene_lightsource(lightSource) {	
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
		GetCollidingMaterialPolygon(ray_in, distance, intersectionPoint, mat, normal);
		GetCollidingMaterialSphere(ray_in, distance, intersectionPoint, mat, normal);

		// Apply lightning
		if(!mat.checkIsLightSource()) {
			ColorDBL intensity = ray_in.GetLightIntensity(normal, scene_lightsource, 10, intersectionPoint, scene_obstacles, scene_spheres);
			mat.changeLuminance(intensity);
			ColorDBL newColor = (mat.getColor()).MultiplyColor(intensity).ClampColors();
			mat.changeColor(newColor);
		}

		// Calculate the color within a mirror
		if (mat.checkIsReflective()) {
			Ray ray = ray_in.reflection(ray_in, normal, intersectionPoint);
			Material newMat = GetCollidingMaterial(ray);
			mat.changeColor(newMat.getColor().mult(0.8));
			// ray_in.PrintRayPath();
		}

		 // Calculate the color of a Lambertian material
		if (mat.checkIsLambertian()) {

			int maxBounces = 5;
			double absorbtionFactor = 0.5;
			double absorbtionChance = 1 - absorbtionFactor;
			float randomFactor = static_cast<float>(rand()) / RAND_MAX;

			// Nuvarande mechanic så att en ray studsar MAX 5 gånger
			if (randomFactor < absorbtionChance && ray_in.getPathLength() <= maxBounces) {
				int renderAmounts = 5;
				ColorDBL leanColor;
				for(int i = 0; i < renderAmounts; i++) {
					Ray ray = ray_in.lambertianReflection(ray_in, normal, intersectionPoint);
					Material newMat = GetCollidingMaterial(ray);

					ColorDBL newColor = mat.getColor().AddColor(newMat.getColor().mult(absorbtionFactor));
					leanColor = leanColor.AddColor(newColor);
				}
				leanColor = leanColor.divide(renderAmounts);
				mat.changeColor(leanColor);
			}
			else {
				mat.changeColor(mat.getColor());
			}
			/*else {
				glm::vec3 colors(0.0f, 0.0f, 0.0f);
				float amountMaterials = 0.0f;
				Ray* currentRay = ray_in.getPathStart();
				
				while (currentRay != nullptr && currentRay->next != nullptr) {
					auto material = currentRay->getCollidedMaterial();
					if (material) {
						colors += material->getColor().getColorGlm();
						amountMaterials++;
					}
					currentRay = currentRay->next;
				}

				if(amountMaterials > 0.0) {
					colors = colors / static_cast<float>(amountMaterials);
					mat.changeColor(ColorDBL(colors));
				}
			}*/
		}

		return mat;
	}
private:
	std::vector<Shape*> scene_shapes;
	std::vector<Shape*> scene_obstacles;
	std::vector<Sphere> scene_spheres;
	Light scene_lightsource;

	void GetCollidingMaterialPolygon(Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal) {
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
						mat = shape->GetMaterial();
						normal = shape->GetNormal();
					}
				}
			}
		}
	}

	void GetCollidingMaterialSphere(Ray ray_in, double& distance, glm::vec3& finalIntersectionPoint, Material& mat, glm::vec3& normal) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		for (Sphere& sphere : scene_spheres) {
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
	//Material GetMirrorMaterial(std::vector<Shape*> shapes_in, Ray& ray_in, glm::vec3 normal_in, glm::vec3 intersectionPoint_in, Light lightSource, std::vector<Sphere> spheres_in) {
	//	Ray ray = ray_in.reflection(ray_in, normal_in, intersectionPoint_in);
	//	Material mat = GetCollidingMaterial(ray, );
	//	return mat;
	//}
};
// TODO: Reference additional headers your program requires here.
