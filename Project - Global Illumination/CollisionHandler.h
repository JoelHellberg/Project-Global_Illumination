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
	struct HitData {
		bool hit = false;
		glm::vec3 point{ 0 };
		glm::vec3 normal{ 0 };
		int objectId = -1;
		Material material;
	};

public:

	CollisionHandler(std::vector<Shape*> room_in, std::vector<Shape*> obstacles_in, std::vector<Sphere> spheres_in, Light lightSource, double noSamples_in, int maxDepth_in)
	: scene_shapes(room_in), scene_obstacles(obstacles_in), scene_spheres(spheres_in), scene_lightsource(lightSource), noSamples(noSamples_in), maxDepth(maxDepth_in){
		for (Shape* obstacle : obstacles_in) {
			scene_shapes.push_back(obstacle);
		}
	}

	// Function that returns the material of the shape that a ray collides with
	Material GetCollidingMaterial(Ray& ray_in);

	void ProcessMaterialProperties(Ray& ray_in, HitData& hit);

	void ProcessLightning(Ray& ray_in, HitData& hit);

	void ProcessMirrorReflection(Ray& ray_in, HitData& hit);

	void ProcessLambertianReflection(Ray& ray_in, HitData& hit);

private:
	std::vector<Shape*> scene_shapes;
	std::vector<Shape*> scene_obstacles;
	std::vector<Sphere> scene_spheres;
	Light scene_lightsource;
	double noSamples;
	int maxDepth;

	glm::vec3 intersectionPoint = { 0, 0, 0 };
	glm::vec3 normal = { 0,0,0 };
	int objectId = 0;

	void GetCollidingMaterialPolygon(
		const Ray& ray_in, double& distance, HitData& hit) const
	{
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();

		for (Shape* shape : scene_shapes) {
			double dotProduct = glm::dot(shape->GetNormal(), rayDirection);
			if (dotProduct < 0.0 && shape->DoesCollide(rayStartPos, rayDirection)) {
				glm::vec3 objectIntersectionPoint = shape->GetIntersectionPoint(rayStartPos, rayDirection);
				double dist = glm::distance(rayStartPos, objectIntersectionPoint);
				if (dist < distance) {
					distance = dist;
					hit.hit = true;
					hit.point = objectIntersectionPoint;
					hit.objectId = shape->getShapeID();
					hit.material = shape->GetMaterial();
					hit.normal = shape->GetNormal();
				}
			}
		}
	}


	void GetCollidingMaterialSphere(
		const Ray& ray_in, double& distance, HitData& hit) {
		glm::vec3 rayStartPos = ray_in.GetPs();
		glm::vec3 rayDirection = ray_in.GetRayDirection();
		
		for (Sphere& sphere : scene_spheres) {
			if (sphere.DoesCollide(rayDirection, rayStartPos)) {
				glm::vec3 objectIntersectionPoint = sphere.GetIntersectionPoint(rayDirection, rayStartPos);
				// Find the object that is closest to the ray's starting position
				if (distance > glm::distance(rayStartPos, objectIntersectionPoint)) {
					hit.point = objectIntersectionPoint;
					distance = glm::distance(rayStartPos, objectIntersectionPoint);
					hit.objectId = sphere.getShapeID();
					hit.material = sphere.GetMaterial();
					hit.normal = sphere.CalculateNormal(rayDirection, rayStartPos);
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
