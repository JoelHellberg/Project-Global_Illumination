// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "ColorDBL.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Triangle {
public:
    Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, ColorDBL color_in) {
        coordinates.push_back(point1); //Coordniates[0]
        coordinates.push_back(point2);//Coordinates[1]
        coordinates.push_back(point3);//Cordinates[2]
        color = color_in;

        normal = glm::cross((point1 - point3), (point2 - point1));
    };

    glm::vec3 GetNormal() {
        return normal;
    }

    ColorDBL FetchColor() {
        return color;
    }

    double CalculateT(glm::vec3 rayDirection);

    glm::vec3 GetIntersectionPoint(Ray ray_in);

    bool DoesCollide(Ray ray_in);

private:
    std::vector <glm::vec3> coordinates;
    ColorDBL color;
    glm::vec3 normal;
};
