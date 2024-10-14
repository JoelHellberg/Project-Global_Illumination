// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "Material.h"
#include "ColorDBL.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class Sphere {
public:

    /*Sphere() = default;*/

    Sphere(const double r, const glm::vec3 center_in, Material material) {
        radius = r;
        center = center_in;
        Spherematerial = material;

    }

    //glm::vec3 GetNormal() const override {
    //    return normal;
    //}

    ColorDBL FetchColor() const {
        return Spherematerial.getColor();
    }

    Material GetMaterial() const {
        return Spherematerial;
    }

    glm::vec3 CalculateNormal(glm::vec3 raydirection, glm::vec3 ps_in);

    //double GetC1() {
    //    return c1;
    //}

    //double GetC2() {
    //    return c2;
    //}

    //double GetC3() {
    //    return c3;
    //}

    glm::vec3 GetIntersectionPoint(glm::vec3 raydirection, glm::vec3 ps_in);

    /*void CalculateC(glm::vec3 center, double radius, glm::vec3 rayDirection);*/


    double CalculateArg(glm::vec3 raydirection, glm::vec3 ps_in);

    bool DoesCollide(glm::vec3 rayDirection, glm::vec3 ps_in);

private:

    double radius;
    glm::vec3 center;
    Material Spherematerial;
};
