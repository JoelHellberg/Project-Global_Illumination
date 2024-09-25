// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "Rectangle.cpp"
#include "ColorDBL.cpp"
#include "ColorDBL.h"
#include "Camera.cpp"
#include <glm/glm.hpp>
#include <vector>


int main()
{
	std::vector<Rectangle> rectangles;
	// Define objects
	Rectangle roof(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(1.0, 0.7, 0.0));
	rectangles.push_back(roof);
	Rectangle floor(glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), ColorDBL(0.0, 1.0, 0.0));
	rectangles.push_back(floor);

	// Walls behind y (x, -6.0, z)
	Rectangle wall1(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 1.0));
	rectangles.push_back(wall1);
	Rectangle wall2(glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, -6.0, 5.0), ColorDBL(1.0, 1.0, 1.0));
	rectangles.push_back(wall2);
	Rectangle wall3(glm::vec3(10.0, -6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), ColorDBL(0.7, 0.7, 0.7));

	rectangles.push_back(wall3);

	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), ColorDBL(0.0, 1.0, 0.0));
	rectangles.push_back(wall4);
	Rectangle wall5(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(0.0, 6.0, -5.0), ColorDBL(0.5, 0.5, 0.5));
	rectangles.push_back(wall5);
	Rectangle wall6(glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(13.0, 0.0, 5.0), ColorDBL(1.0, 0.0, 0.0));
	rectangles.push_back(wall6);

	Camera myCamera = Camera(800.0, 800.0);

	for (double i = 0.0; i < 800.0; i++) {
		for (double j = 0.0; j < 800.0; j++) {
			glm::vec3 rayDirection = myCamera.GetRayDirection(i, j);
			for (Rectangle r : rectangles) {
				double dotProduct = glm::dot(r.GetNormal(), rayDirection);
				if (dotProduct < 0.0) {
					ColorDBL pixelColor = r.FetchColor();
					if (pixelColor.getColor() == std::vector<double>({ 0.7, 0.7, 0.7 })
						|| pixelColor.getColor() == std::vector<double>({ 1.0, 0.0, 0.0 })) {
						ColorDBL::displayColor(pixelColor.getColor());
					}
					break;
				}
			}
		}
	}

	std::cout << "Hello CMake." << std::endl;
	return 0;


}