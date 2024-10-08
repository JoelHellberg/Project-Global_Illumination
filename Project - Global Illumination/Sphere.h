// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Shape.h"

class Sphere : public Shape {
public:

    /*Sphere() = default;*/

    Sphere(const double& r, const glm::vec3& center, Material material) {
        radius = r;
        Center = center;
        Spherematerial = material;

    }

    //glm::vec3 GetNormal() const override {
    //    return normal;
    //}

    ColorDBL FetchColor() const override {
        return Spherematerial.getColor();
    }

    Material GetMaterial() const override {
        return Spherematerial;
    }

    glm::vec3 GetNormal() const override {
        return normal;
    }

    double GetC1() {
        return c1;
    }

    double GetC2() {
        return c2;
    }

    double GetC3() {
        return c3;
    }

    glm::vec3 GetIntersectionPoint(glm::vec3 raydirection, glm::vec3 center) const override;

    void CalculateC(glm::vec3 center, double radius, glm::vec3 rayDirection);

    float CalculateT(glm::vec3 raydirection, glm::vec3 center) const;

    double CalculateArg(glm::vec3 raydirection, glm::vec3 center) const;

    bool DoesCollide(glm::vec3 ps, glm::vec3 rayDirection) const override;

private:

    double radius;
    glm::vec3 Center;
    Material Spherematerial;
    glm::vec3 normal;
    double c1;
    double c2;
    double c3;
};
