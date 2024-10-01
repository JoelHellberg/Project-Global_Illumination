// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Triangle.h"
#include "Ray.h"

double Triangle::CalculateT(Ray ray_in)  const {

    glm::vec3 ps = ray_in.GetPs();
    glm::vec3 T = ps - coordinates[0];
    glm::vec3 E_one = coordinates[0] - coordinates[2];
    glm::vec3 E_two = coordinates[1] - coordinates[0];
    glm::vec3 D = ray_in.GetRayDirection();

    glm::vec3 P = glm::cross(D, E_two);
    glm::vec3 Q = glm::cross(T, E_one);

    double t = glm::dot(Q, E_two) / glm::dot(P, E_one);

    return t;
}

glm::vec3 Triangle::GetIntersectionPoint(Ray ray_in) const {
    glm::vec3 rayDirection = ray_in.GetRayDirection();
    glm::vec3 ps = ray_in.GetPs();
    float t = CalculateT(ray_in);

    return ps + t * rayDirection;
}

bool Triangle::DoesCollide(Ray ray_in) const {
    glm::vec3 v = coordinates[0];
    glm::vec3 c1 = coordinates[2] - coordinates[0];
    glm::vec3 c2 = coordinates[1] - coordinates[0];

    //std::cout << "C1 = " << c1.x << " " << c1.y << " " << c1.z;
    //std::cout << "C2 = " << c2.x << " " << c2.y << " " << c2.z;

    float t = CalculateT(ray_in);

    glm::vec3 xi = GetIntersectionPoint(ray_in);
    double a = glm::dot((xi - v), c1) / glm::dot(c1, c1);
    double b = glm::dot((xi - v), c2) / glm::dot(c2, c2);
    return (a >= 0.0 && b >= 0.0) && (a + b <= 1.0);
}