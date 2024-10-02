// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Ray.h"

//do: Outgoing ray direction
//di: Incoming ray direction
//N = Surface normal
//x = intersection point



// do  = di - 2(di*N)*N

Ray Ray::reflection(Ray ray_in, glm::vec3 surface_normal, glm::vec3 intersectionPoint) {
	surface_normal = glm::normalize(surface_normal);
	glm::vec3 di = glm::normalize(ray_in.GetRayDirection());

	if (glm::dot(di, surface_normal) > 0.0f) {
		surface_normal = -surface_normal;  // Flip the normal
	}

	glm::vec3 d_o = di - 2.0f * glm::dot(di, surface_normal) * surface_normal;

	Ray* reflected_ray = new Ray(d_o, intersectionPoint);
	AddRayToList(reflected_ray);
	// Material new_mat = mat;

	return *reflected_ray;


}

void Ray::AddRayToList(Ray* newRay) {
	this->next = newRay;
}

//void Ray::AddToList(glm::vec3 newIntersectionPoint, Material mat) {
//
//	Ray* newRay = new Ray(1, 2, 3);
//
//	if (!head) {
//		newRay = head;
//		newRay->next = nullptr;
//	}
//	else {
//
//		Ray* temp = newRay;
//
//		for (Ray* temp = head; temp != nullptr; temp = temp->next) {
//			
//			if (temp->next == nullptr) {
//
//				temp->next = newRay;
//				newRay->next = nullptr;
//			}
//
//			temp = temp->next;
//		}
//	}
//}
