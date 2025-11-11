// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Light.h"
#include <random>

glm::vec3 Light::RandomPointOnLight() {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float si = dist(gen);
    float ti = dist(gen);

    glm::vec3 E1 = ReturnE1();
    glm::vec3 E2 = ReturnE2();

    return coordinates[0] + si * E1 + ti * E2;
}


