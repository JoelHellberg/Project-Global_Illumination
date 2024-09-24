// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "Rectangle.cpp"
#include "ColorDBL.cpp"
#include "Camera.cpp"
#include <glm/glm.hpp>
#include <vector>


int main()
{
	std::vector<Rectangle> rectangles;
	// Define objects
	Rectangle roof(glm::vec3(0.0, 0.6, 5.0), glm::vec3(10.0, 0.6, 5.0), glm::vec3(10.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(roof);
	Rectangle floor(glm::vec3(0.0, 0.6, -5.0), glm::vec3(0.0, 0.0, -5.0), glm::vec3(10.0, 0.0, -5.0), glm::vec3(10.0, 0.6, -5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(floor);

	// Walls behind y (x, -6.0, z)
	Rectangle wall1(glm::vec3(-3.0, -6.0, 5.0), glm::vec3(-3.0, -6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall1);
	Rectangle wall2(glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall2);
	Rectangle wall3(glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(13.0, -6.0, -5.0), glm::vec3(13.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall3);

	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 6.0, 5.0), glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(-3.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall4);
	Rectangle wall5(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(0.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall5);
	Rectangle wall6(glm::vec3(10.0, 6.0, 5.0), glm::vec3(13.0, 6.0, 5.0), glm::vec3(13.0, 6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));
	rectangles.push_back(wall6);

	Camera myCamera = Camera(800.0, 800.0);

	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			glm::vec3 rayDirection = myCamera.GetRayDirection(i, j);
			for (Rectangle r : rectangles) {
				double dotProduct = glm::dot(r.GetNormal(), rayDirection);
				if (dotProduct < 0) {
					ColorDBL pixelColor = r.GetColor();
				}
			}
		}
	}

	std::cout << "Hello CMake." << std::endl;
	return 0;


}