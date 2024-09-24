// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "Rectangle.cpp"
#include "ColorDBL.cpp"
#include <glm/glm.hpp>

int main()
{
	// Define objects
	Rectangle roof(glm::vec3(0.0, 0.6, 5.0), glm::vec3(10.0, 0.6, 5.0), glm::vec3(10.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	Rectangle floor(glm::vec3(0.0, 0.6, -5.0), glm::vec3(0.0, 0.0, -5.0), glm::vec3(10.0, 0.0, -5.0), glm::vec3(10.0, 0.6, -5.0), ColorDBL(0.0, 0.0, 0.0));
	
	// Walls behind y (x, -6.0, z)
	Rectangle wall1(glm::vec3(-3.0, -6.0, 5.0), glm::vec3(-3.0, -6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	Rectangle wall2(glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	Rectangle wall3(glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(13.0, -6.0, -5.0), glm::vec3(13.0, -6.0, 5.0), ColorDBL(0.0, 0.0, 0.0));
	
	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 6.0, 5.0), glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(-3.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));
	Rectangle wall5(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(0.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));
	Rectangle wall6(glm::vec3(10.0, 6.0, 5.0), glm::vec3(13.0, 6.0, 5.0), glm::vec3(13.0, 6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), ColorDBL(0.0, 0.0, 0.0));


	std::cout << "Hello CMake." << std::endl;
	return 0;


}