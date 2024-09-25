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
        coordinates[0] = point1;
        coordinates[1] = point2;
        coordinates[2] = point3;
        color = color_in;

        normal = glm::cross((point3 - point1), (point2 - point1));
    };
    glm::vec3 GetNormal() {
        return normal;
    }

    ColorDBL FetchColor() {
        return color;
    }
private:
    glm::vec3 coordinates[3];
    ColorDBL color;
    glm::vec3 normal;
};
