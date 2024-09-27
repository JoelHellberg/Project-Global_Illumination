// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"

#include "ColorDBL.h"
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

Material processIntersection(auto& shapes, Ray ray, Material mat, glm::vec3& normal, glm::vec3& intersectionPoint) {
	for (auto shape : shapes) {
		double dotProduct = glm::dot(shape.GetNormal(), ray.GetRayDirection());
		if (dotProduct < 0.0) {
			if (shape.DoesCollide(ray)) {
				mat = shape.GetMaterial();
				normal = shape.GetNormal();
				intersectionPoint = shape.GetIntersectionPoint(ray);
				break;
			}
		}
	}
	return mat;
}

int main()
{
	//Vectors which saves the shapes of the scene
	std::vector<Rectangle> rectangles = defineRectangles();
	std::vector<Triangle> triangles = defineTriangles();


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
			Material mat = Material();

			std::vector<double> colorValues = { 0, 0, 0 };
			glm::vec3 intersectionPoint = {0, 0, 0};
			number_of_reflections++;


			bool continueLoop = true;
			bool hasColided = false;
			while(continueLoop) {
				glm::vec3 normal = {0, 0, 0};
				mat = processIntersection(rectangles, ray, mat, normal, intersectionPoint);
				mat = processIntersection(triangles, ray, mat, normal, intersectionPoint);
				if(mat.checkIsReflective() && (normal != glm::vec3{0, 0, 0})) {
					hasColided = true;
					//std::cout << "Ray #" << number_of_reflections << " direction before : (" << ray.GetRayDirection().x << ", " << ray.GetRayDirection().y << ", " << ray.GetRayDirection().z << ")\n";
					//std::cout << "Material collided with: " << mat.getColor().getColor()[0] << " " << mat.getColor().getColor()[1] << " " << mat.getColor().getColor()[2] << "\n";
					//ray.reflect(ray.GetRayDirection(),normal,mat, intersectionPoint);
					ray = ray.reflection(ray.GetRayDirection(),normal,mat, intersectionPoint);
					glm::vec3 test = ray.GetRayDirection();
					// std::cout << "Normal: " << "( " <<  normal.x << " , " << normal.y << " , " << normal.z << ")" << "\n";
					// std::cout << "Ray #" << number_of_reflections << " direction after : (" << ray.GetRayDirection().x << ", " << ray.GetRayDirection().y << ", " << ray.GetRayDirection().z << ")\n";
					// std::cout << "Ray #" << number_of_reflections << " starting point : (" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ")\n";

					}
				else {
					if(hasColided) {
						// std::cout << "Material collided with: " << mat.getColor().getColor()[0] << " " << mat.getColor().getColor()[1] << " " << mat.getColor().getColor()[2] << "\n";
						// std::cout << "Normal: " << "( " <<  normal.x << " , " << normal.y << " , " << normal.z << ")" << "\n";
					}
					continueLoop = false;
				
				}
			}

			colorValues = mat.getColor().getColor();
			// Print the color of the wall where collision was detected
			printColor(colorValues);
		}
	}

	/*for (int i = 0; i < detectedColors.size(); i++) {
		ColorDBL::displayColor(detectedColors[i]);
		std::cout << "number of occurences: " << occurences[i] << "\n\n";
	}*/

	return 0;


}
