// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "CollisionHandler.h"

#include "ColorDBL.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Camera.h"
#include "Ray.h"
#include "Material.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

//Define rectangles in scene
std::vector<Rectangle> defineRectangles() {
	// Define objects
	std::vector<Rectangle> rectangles_out;

	 //Define Roof & Floor
	Rectangle roof(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), false));
	rectangles_out.push_back(roof);
	Rectangle floor(glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), false)); 
	rectangles_out.push_back(floor);

	// Walls behind y (x, -6.0, z)
	Rectangle wall1(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), Material(ColorDBL(0.0, 0.0, 1.0), false));
	rectangles_out.push_back(wall1);
	Rectangle wall2(glm::vec3(0.0, -6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), Material(ColorDBL(0.0, 1.0, 0.0), false));
	rectangles_out.push_back(wall2);
	Rectangle wall3(glm::vec3(10.0, -6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), Material( ColorDBL(1.0, 1.0, 1.0), true)); 
	rectangles_out.push_back(wall3);

	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, 6.0, 5.0), Material(ColorDBL(0.0, 1.0, 0.7),false));
	rectangles_out.push_back(wall4);
	Rectangle wall5(glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, 6.0, 5.0), Material(ColorDBL(0.0, 0.0, 1.0),false)); 
	rectangles_out.push_back(wall5);
	Rectangle wall6(glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(13.0, 0.0, 5.0), Material(ColorDBL(1.0, 0.0, 0.0), false)); 
	rectangles_out.push_back(wall6);

	return rectangles_out;
}

//Define triangles in scene
std::vector<Triangle> defineTriangles() {
	std::vector<Triangle> triangles_out;

	// Define the floor (in front of the camera) as two orthogonal triangles
	Triangle floorFrontL(glm::vec3(10.0, 0.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, 6.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), false));
	triangles_out.push_back(floorFrontL);
	Triangle floorFrontR(glm::vec3(10.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), Material(ColorDBL(0.5, 0.5, 0.5), false));
	triangles_out.push_back(floorFrontR);

	// Define the floor (behind the camera) as two orthogonal triangles
	Triangle floorBehindL(glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), Material(ColorDBL(0.3, 1.0, 0.7), false));
	triangles_out.push_back(floorBehindL);
	Triangle floorBehindR(glm::vec3(0.0, 0.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, -6.0, -5.0), Material(ColorDBL(0.3, 1.0, 0.7), false));
	triangles_out.push_back(floorBehindR);

	// Define the roof (behind the camera) as two orthogonal triangles
	Triangle roofBehindL(glm::vec3(0.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, 6.0, 5.0), Material(ColorDBL(0.0, 8.0, 0.0), false));
	triangles_out.push_back(roofBehindL);
	Triangle roofBehindR(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, -6.0, 5.0), glm::vec3(-3.0, 0.0, 5.0), Material(ColorDBL(0.0, 8.0, 0.0), false));
	triangles_out.push_back(roofBehindR);

	// Define the roof (in front of the camera) as two orthogonal triangles
	Triangle roofFrontL(glm::vec3(10.0, 0.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), false));
	triangles_out.push_back(roofFrontL);
	Triangle roofFrontR(glm::vec3(10.0, 0.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(10.0, -6.0, 5.0), Material(ColorDBL(0.5, 0.5, 0.5), false));
	triangles_out.push_back(roofFrontR);

	return triangles_out;
}

//Print all color in a column
void printColor(std::vector<double> colorValues_in) {

	ColorDBL::displayColor(colorValues_in);
}

int main()
{
	//Vectors which saves the shapes of the scene
	std::vector<Shape*> shapes;

	std::vector<Rectangle> rectangles = defineRectangles();
	std::vector<Triangle> triangles = defineTriangles();

	for (Rectangle& rectangle : rectangles) {
		Shape* dummy_shape = &rectangle;
		shapes.push_back(dummy_shape);
	}
	for (Triangle& triangle : triangles) {
		Shape* dummy_shape = &triangle;
		shapes.push_back(dummy_shape);
	}


	//Dimension of the output image
	double dimensions = 600.0;

	//Camera
	Camera myCamera = Camera(dimensions, dimensions);

	//Std::cout for the ppm-format
	std::cout << "P3" << "\n";//ppm
	std::cout << " " << dimensions << " " << " " << dimensions << " " << "\n"; //Dimensions for the image
	std::cout << "255" << "\n"; //Define that RGB is used

	int number_of_reflections = 0;
	for (double i = dimensions - 1.0; i >= 0.0; i--) {
		for (double j = dimensions - 1.0; j >= 0.0; j--) {

			Ray ray = myCamera.GetRay(j, i);

			Material mat = CollisionHandler().GetCollidingMaterial(shapes, ray);

			// Print the color of the wall where collision was detected
			printColor(mat.getColor().getColor());
		}
	}

	return 0;


}
