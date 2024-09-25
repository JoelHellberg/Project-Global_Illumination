// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "ColorDBL.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Triangle {
public:
    Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, ColorDBL color_in) {
        coordinates.push_back(point1);
        coordinates.push_back(point2);
        coordinates.push_back(point3);
        color = color_in;

        normal = glm::cross((point3 - point1), (point2 - point1));
    };

    glm::vec3 GetNormal() {
        return normal;
    }

    glm::vec3 GetV() {
        return coordinates[0];
    }
    glm::vec3 GetC1() {
        return coordinates[1] - coordinates[0];
    }
    glm::vec3 GetC2() {
        return coordinates[2] - coordinates[0];
    }

    ColorDBL FetchColor() {
        return color;
    }
private:
    std::vector <glm::vec3> coordinates;
    ColorDBL color;
    glm::vec3 normal;
};
