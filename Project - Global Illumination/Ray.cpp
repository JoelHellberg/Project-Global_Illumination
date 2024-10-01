// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Ray.h"

//do: Outgoing ray direction
//di: Incoming ray direction
//N = Surface normal
//x = intersection point



// do  = di - 2(di*N)*N

Ray Ray::reflection(glm::vec3 di, glm::vec3 surface_normal, glm::vec3 intersectionPoint) {
	surface_normal = glm::normalize(surface_normal);
	di = glm::normalize(di);

	if (glm::dot(di, surface_normal) > 0.0f) {
		surface_normal = -surface_normal;  // Flip the normal
	}

	glm::vec3 d_o = di - 2.0f * glm::dot(di, surface_normal) * surface_normal;


	Ray reflected_ray = Ray(d_o, intersectionPoint);
	// Material new_mat = mat;

	return reflected_ray;


}

void Ray::reflect(glm::vec3 di, glm::vec3 surface_normal, Material mat, glm::vec3 intersectionPoint) {
	surface_normal = glm::normalize(surface_normal);
	di = glm::normalize(di);

	if (glm::dot(di, surface_normal) > 0.0f) {
		surface_normal = -surface_normal;  // Flip the normal
	}

	glm::vec3 d_o = di - 2.0f * glm::dot(di, surface_normal) * surface_normal;

	rayDirection = d_o;

}