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

	ColorDBL shadowIntensity = ColorDBL(0.0, 0.0, 0.0);

	double area = lightSource.GetArea();

	double sumResult = 0.0;

	for (int i = 0; i < raysAmount; i++) {
		glm::vec3 pointOnLight = lightSource.RandomPointOnLight();
		glm::vec3 lightRayDirection = intersectionPoint - pointOnLight;

		bool hitsObject = true;

		glm::vec3 pointOnObject = intersectionPoint;
	
		Ray GetLightIntensity(pointOnObject, glm::normalize(lightRayDirection));

		for (Shape* shape : shapes_in) {
			double dotProduct = glm::dot(shape->GetNormal(), lightRayDirection);
			if (dotProduct < 0.0) {
				if (shape->DoesCollide(pointOnLight, lightRayDirection)) {
					glm::vec3 intersectionPointNew = shape->GetIntersectionPoint(pointOnLight, lightRayDirection);
					if (glm::distance(pointOnLight, intersectionPointNew) < glm::distance(pointOnLight, intersectionPoint)) {
						hitsObject = false;
						break;
					}
				}
			}
		}

		if (hitsObject) {
			double cosX = glm::dot(surfaceNormal, lightRayDirection) / glm::length(lightRayDirection);
			double cosY = glm::dot(-LightSourceNormal, lightRayDirection) / glm::length(lightRayDirection);

			sumResult += (cosX * cosY) / std::pow(glm::length(lightRayDirection), 2.0);
		}

	}

		double luminance = ((area * 10.0f) / ((float)M_PI * raysAmount)) * sumResult;
		shadowIntensity += ColorDBL(luminance, luminance, luminance);

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
