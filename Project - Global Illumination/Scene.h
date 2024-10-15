// Project - Global Illumination.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "CollisionHandler.h"

#include "ColorDBL.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Camera.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "Sphere.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>


//Define rectangles in scene
std::vector<Rectangle> defineRectangles() {
	// Define objects
	std::vector<Rectangle> rectangles_out;

	//Define Roof & Floor
	Rectangle roof(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	rectangles_out.push_back(roof);
	Rectangle floor(glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	rectangles_out.push_back(floor);

	// Walls behind y (x, -6.0, z)
	Rectangle wallBack(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	rectangles_out.push_back(wallBack);
	Rectangle wallRight(glm::vec3(0.0, -6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), Material(ColorDBL(0.1, 1.0, 0.1), "lambertian"));
	rectangles_out.push_back(wallRight);
	Rectangle wallFrontR(glm::vec3(10.0, -6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), Material(ColorDBL(1.0, 1.0, 1.0), "mirror"));
	rectangles_out.push_back(wallFrontR);

	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, 6.0, 5.0), Material(ColorDBL(1.0, 0.1, 1.0), "lambertian"));
	rectangles_out.push_back(wall4);
	Rectangle wallLeft(glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, 6.0, 5.0), Material(ColorDBL(0.1, 0.1, 1.0), "lambertian"));
	rectangles_out.push_back(wallLeft);
	Rectangle wallFrontLeft(glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(13.0, 0.0, 5.0), Material(ColorDBL(1.0, 0.1, 0.1), "lambertian"));
	rectangles_out.push_back(wallFrontLeft);


	return rectangles_out;
}

//Define triangles in scene
std::vector<Triangle> defineTriangles() {
	std::vector<Triangle> triangles_out;

	// Define the floor (in front of the camera) as two orthogonal triangles
	Triangle floorFrontL(glm::vec3(10.0, 0.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, 6.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(floorFrontL);
	Triangle floorFrontR(glm::vec3(10.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(floorFrontR);

	// Define the floor (behind the camera) as two orthogonal triangles
	Triangle floorBehindL(glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(floorBehindL);
	Triangle floorBehindR(glm::vec3(0.0, 0.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, -6.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(floorBehindR);

	// Define the roof (behind the camera) as two orthogonal triangles
	Triangle roofBehindL(glm::vec3(0.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, 6.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(roofBehindL);
	Triangle roofBehindR(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, -6.0, 5.0), glm::vec3(-3.0, 0.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(roofBehindR);

	// Define the roof (in front of the camera) as two orthogonal triangles
	Triangle roofFrontL(glm::vec3(10.0, 0.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(roofFrontL);
	Triangle roofFrontR(glm::vec3(10.0, 0.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(10.0, -6.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), "lambertian"));
	triangles_out.push_back(roofFrontR);

	return triangles_out;
}

std::vector<Rectangle> defineObstaclesRectangles() {
	std::vector<Rectangle> rectangles_out;

	// Floor of Tetraed
	Rectangle tetraFloor(glm::vec3(6.0, 4.0, -3.0), glm::vec3(8.0, 4.0, -3.0), glm::vec3(8.0, 2.0, -3.0), glm::vec3(6.0, 2.0, -3.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	rectangles_out.push_back(tetraFloor);

	return rectangles_out;
}

std::vector<Triangle> defineObstaclesTriangles() {
	std::vector<Triangle> triangles_out;

	// Triangles of Tetraed
	Triangle rightWallTetraedLeft(glm::vec3(7.0, 4.0, -3.0), glm::vec3(7.0, 3.0, 1.0), glm::vec3(8.0, 4.0, -3.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(rightWallTetraedLeft);
	Triangle rightWallTetraedRight(glm::vec3(7.0, 4.0, -3.0), glm::vec3(6.0, 4.0, -3.0), glm::vec3(7.0, 3.0, 1.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(rightWallTetraedRight);

	// Egentiligen fram
	Triangle leftWallTetraedLeft(glm::vec3(6.0, 3.0, -3.0), glm::vec3(7.0, 3.0, 1.0), glm::vec3(6.0, 4.0, -3.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(leftWallTetraedLeft);
	Triangle leftWallTetraedRight(glm::vec3(6.0, 3.0, -3.0), glm::vec3(6.0, 2.0, -3.0), glm::vec3(7.0, 3.0, 1.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(leftWallTetraedRight);

	// Egentligen höger
	Triangle frontWallTetraedLeft(glm::vec3(7.0, 2.0, -3.0), glm::vec3(7.0, 3.0, 1.0), glm::vec3(6.0, 2.0, -3.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(frontWallTetraedLeft);
	Triangle frontWallTetraedRight(glm::vec3(7.0, 2.0, -3.0), glm::vec3(8.0, 2.0, -3.0), glm::vec3(7.0, 3.0, 1.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(frontWallTetraedRight);

	// Egentligen bakifrån
	Triangle backWallTetraedLeft(glm::vec3(8.0, 3.0, -3.0), glm::vec3(7.0, 3.0, 1.0), glm::vec3(8.0, 2.0, -3.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(backWallTetraedLeft);
	Triangle backWallTetraedRight(glm::vec3(8.0, 3.0, -3.0), glm::vec3(8.0, 4.0, -3.0), glm::vec3(7.0, 3.0, 1.0), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	triangles_out.push_back(backWallTetraedRight);

	return triangles_out;
}

std::vector<Sphere> defineSphere(){

	std::vector<Sphere> sphere_out;

	Sphere sphere(1.0, glm::vec3(10, 0, -4), Material(ColorDBL(1.0, 1.0, 0.1), "lambertian"));
	sphere_out.push_back(sphere);

	return sphere_out;
	
}


