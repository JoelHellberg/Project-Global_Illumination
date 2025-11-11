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
	//AddRayToList(reflected_ray);
	// Material new_mat = mat;

	return *reflected_ray;


}

Ray Ray::lambertianReflection(Ray ray_in, glm::vec3 surface_normal, glm::vec3 intersectionPoint) {
	// Thread-safe random generator
	static thread_local std::mt19937 gen(std::random_device{}());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	// Cosine-weighted hemisphere sampling
	float r1 = dist(gen);
	float r2 = dist(gen);

	float theta = acosf(sqrtf(1.0f - r1));  // polar angle
	float phi = 2.0f * M_PI * r2;           // azimuthal angle

	// Local coordinates (cosine-weighted hemisphere)
	float x = sinf(theta) * cosf(phi);
	float y = sinf(theta) * sinf(phi);
	float z = cosf(theta);

	// Build orthonormal basis around the normal
	glm::vec3 up = (fabs(surface_normal.z) < 0.999f) ? glm::vec3(0.0, 0.0, 1.0) : glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 tangent = glm::normalize(glm::cross(up, surface_normal));
	glm::vec3 bitangent = glm::normalize(glm::cross(surface_normal, tangent));

	// Transform from local to world space
	glm::vec3 d_o = glm::normalize(x * tangent + y * bitangent + z * surface_normal);

	// Offset origin slightly to avoid self-intersection
	glm::vec3 origin = intersectionPoint + surface_normal * 1e-4f;

	return Ray(d_o, origin);
}


void Ray::AddRayToList(Ray* newRay) {
	newRay->head = this->head;
	this->next = newRay;
	head->pathLength++;
}

ColorDBL Ray::GetLightIntensity(glm::vec3 normal, Light lightSource, double raysAmount, glm::vec3 intersectionPoint, std::vector<Shape*> obstacles_in, std::vector<Sphere> spheres_in, int shapeId) const {
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

		for (Shape* shape : obstacles_in) {
			if(shape->getShapeID() != shapeId) {
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
		}

		for (Sphere& sphere : spheres_in) {
			if (sphere.getShapeID() != shapeId) {
				if (sphere.DoesCollide(lightRayDirection, pointOnLight)) {
					glm::vec3 intersectionPointNew = sphere.GetIntersectionPoint(lightRayDirection, pointOnLight);
					// Find the object that is closest to the ray's starting position
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

		double luminance = ((area*20.0) / ((float)M_PI * raysAmount)) * sumResult;
		shadowIntensity += ColorDBL(luminance, luminance, luminance);
		// std::cout << "luminance: " << luminance;
		//luminance = std::clamp(luminance, 0.0, 1.0);

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
