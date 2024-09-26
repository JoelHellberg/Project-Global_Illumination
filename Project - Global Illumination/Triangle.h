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
        coordinates.push_back(point1); //Coordniates[0]
        coordinates.push_back(point2);//Coordinates[1]
        coordinates.push_back(point3);//Cordinates[2]
        color = color_in;

        normal = glm::cross((point1 - point3), (point2 - point1));
    };

    glm::vec3 GetNormal() {
        return normal;
    }

    glm::vec3 GetV() {
        return coordinates[0];
    }
    glm::vec3 GetC1() {

        return coordinates[0] - coordinates[2];
    }
    glm::vec3 GetC2() {
        return coordinates[1] - coordinates[0];
    }

    std::vector <glm::vec3>  GetCoordinates() {
        return coordinates;
    }

    ColorDBL FetchColor() {
        return color;
    }
private:
    std::vector <glm::vec3> coordinates;
    ColorDBL color;
    glm::vec3 normal;
};
