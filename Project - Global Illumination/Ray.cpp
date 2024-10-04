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

ColorDBL Ray::GetLightIntensity(glm::vec3 normal, Light lightSource, int raysAmount, glm::vec3 intersectionPoint, std::vector<Shape*> shapes_in) {
	glm::vec3 surfaceNormal = normal;
	glm::vec3 LightSourceNormal(0.0, 0.0, -1.0);

	double area = lightSource.GetArea() * 10.0;

	double sumResult = 0;

	for (int i = 0; i < raysAmount; i++) {
		glm::vec3 randomPoint = lightSource.RandomPointOnLight();
		glm::vec3 lightRay = randomPoint - intersectionPoint;

		Ray lightRayRay = Ray(lightRay, randomPoint);

		bool hitsObject = true;

		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), lightRayRay.GetRayDirection());
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(lightRayRay.GetPs(), lightRayRay.GetRayDirection())) {
					glm::vec3 intersectionPointNew = shape->GetIntersectionPoint(lightRayRay.GetPs(), lightRayRay.GetRayDirection());
					if (glm::distance(randomPoint, intersectionPointNew) < glm::distance(randomPoint, intersectionPoint)) {
						hitsObject = false;
						break;
					}
				}
			}
		}

		if (hitsObject) {
			double cosX = glm::dot(surfaceNormal, lightRay) / glm::length(lightRay);
			double cosY = glm::dot(-LightSourceNormal, lightRay) / glm::length(lightRay);

			sumResult += (cosX * cosY) / std::pow(glm::length(lightRay), 2.0);
		}

	}

		// Clamp the luminance to be between 0 and 1
		double luminance = ((area) / ((float)M_PI * raysAmount)) * sumResult;
		luminance = std::clamp(luminance, 0.0, 1.0);

		return ColorDBL(luminance, luminance, luminance);
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
