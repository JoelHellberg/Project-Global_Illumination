// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "CollisionHandler.h"
#include <glm/glm.hpp>

// Function that returns the material of the shape that a ray collides with
Material CollisionHandler::GetCollidingMaterial(Ray& ray_in) {
	HitData hit;
	hit.material = Material();

	// Local temporary variables
	double distance = std::numeric_limits<double>::max();

	// Perform collision checks locally
	GetCollidingMaterialPolygon(ray_in, distance, hit);
	GetCollidingMaterialSphere(ray_in, distance, hit);

	ProcessMaterialProperties(ray_in, hit);

	return hit.material;
}


void CollisionHandler::ProcessMaterialProperties(Ray& ray_in, HitData& hit) {
	if (!hit.material.checkIsLightSource()) {
		ProcessLightning(ray_in, hit);
	}
	if (hit.material.checkIsReflective()) {
		ProcessMirrorReflection(ray_in, hit);
	}
	if (hit.material.checkIsLambertian()) {
		ProcessLambertianReflection(ray_in, hit);
	}
}


void CollisionHandler::ProcessLightning(Ray& ray_in, HitData& hit) {
	ColorDBL intensity = ray_in.GetLightIntensity(
		hit.normal, scene_lightsource, 5, hit.point, scene_obstacles, scene_spheres, hit.objectId);

	hit.material.changeLuminance(intensity);
	ColorDBL newColor = (hit.material.getColor() * intensity).ClampColors();
	hit.material.changeColor(newColor);
}


void CollisionHandler::ProcessMirrorReflection(Ray& ray_in, HitData& hit) {
	Ray reflected = ray_in.reflection(ray_in, hit.normal, hit.point);
	Material newMat = GetCollidingMaterial(reflected);
	hit.material.changeColor(newMat.getColor() * 0.8);
}


void CollisionHandler::ProcessLambertianReflection(Ray& ray_in, HitData& hit) {
	double albedo = 0.95;  // surface reflectivity
	constexpr double invPi = 1.0 / glm::pi<double>();

	double absorptionChance = 0.2;
	float randomFactor = static_cast<float>(rand()) / RAND_MAX;

	if ((randomFactor > absorptionChance && ray_in.getPathLength() <= maxDepth)) {
		// Generate a random reflected ray over hemisphere
		Ray ray = ray_in.lambertianReflection(ray_in, hit.normal, hit.point);

		double cosOmega = glm::dot(hit.normal, ray.GetRayDirection())
			/ (glm::length(hit.normal) * glm::length(ray.GetRayDirection()));

		Material newMat = GetCollidingMaterial(ray);

		// Include albedo and normalization
		ColorDBL reflectiveColor = newMat.getColor() * (albedo * invPi * cosOmega);
		ColorDBL bounced = newMat.getColor() * reflectiveColor; // multiply colors (energy transfer)

		// Mix reflected color into surface
		ColorDBL newColor = hit.material.getColor() + reflectiveColor;
		hit.material.changeColor(newColor.ClampColors());
	}
}

