// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "CollisionHandler.h"
#include <glm/glm.hpp>

// Function that returns the material of the shape that a ray collides with
Material CollisionHandler::GetCollidingMaterial(Ray ray_in) {
	intersectionPoint = { 0, 0, 0 };
	normal = { 0,0,0 };
	double distance = std::numeric_limits<double>::max();
	Material mat = Material();

	// Find the objects ("shape") that the ray collides with
	objectId = 0;
	GetCollidingMaterialPolygon(ray_in, distance, mat);
	GetCollidingMaterialSphere(ray_in, distance, mat);

	ProcessMaterialProperties(ray_in, mat);

	return mat;
}

void CollisionHandler::ProcessMaterialProperties(Ray ray_in, Material& mat_in) {

	// Apply lightning
	if (!mat_in.checkIsLightSource()) { ProcessLightning(ray_in, mat_in); }

	// Calculate the color within a mirror
	if (mat_in.checkIsReflective()) { ProcessMirrorReflection(ray_in, mat_in); }

	// Calculate the color of a Lambertian material
	if (mat_in.checkIsLambertian()) { ProcessLambertianReflection(ray_in, mat_in); }

}

void CollisionHandler::ProcessLightning(Ray ray_in, Material& mat_in) {
	ColorDBL intensity = ray_in.GetLightIntensity(normal, scene_lightsource, 5, intersectionPoint, scene_obstacles, scene_spheres, objectId);
	mat_in.changeLuminance(intensity);
	ColorDBL newColor = (mat_in.getColor() * intensity).ClampColors();
	mat_in.changeColor(newColor);
}

void CollisionHandler::ProcessMirrorReflection(Ray ray_in, Material& mat_in) {
	Ray ray = ray_in.reflection(ray_in, normal, intersectionPoint);
	Material newMat = GetCollidingMaterial(ray);
	mat_in.changeColor(newMat.getColor() * 0.8);
}

void CollisionHandler::ProcessLambertianReflection(Ray ray_in, Material& mat_in) {

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

		ColorDBL newColor = mat_in.getColor() + reflectiveColor;
		mat_in.changeColor(newColor);
	}
	else {
		mat_in.changeColor(mat_in.getColor());
	}
}