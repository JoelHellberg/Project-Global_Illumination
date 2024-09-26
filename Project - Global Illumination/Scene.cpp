// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "Rectangle.cpp"
#include "ColorDBL.cpp"
#include "ColorDBL.h"
#include "Camera.cpp"
#include "Triangle.cpp"
#include "Ray.cpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

std::vector<Rectangle> defineRectangles() {
	// Define objects
	std::vector<Rectangle> rectangles_out;

	// Define Roof & Floor
	Rectangle roof(glm::vec3(0.0, 6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(1.0, 0.7, 0.0)); // Hittas
	rectangles_out.push_back(roof);
	Rectangle floor(glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), ColorDBL(0.0, 1.0, 0.0)); // Hittas
	rectangles_out.push_back(floor);

	// Walls behind y (x, -6.0, z)
	Rectangle wall1(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, -6.0, 5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(-3.0, 0.0, -5.0), ColorDBL(0.0, 0.0, 1.0));
	rectangles_out.push_back(wall1);
	Rectangle wall2(glm::vec3(0.0, -6.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, -6.0, -5.0), glm::vec3(0.0, -6.0, -5.0), ColorDBL(1.0, 1.0, 1.0)); // Hittas
	rectangles_out.push_back(wall2);
	Rectangle wall3(glm::vec3(10.0, -6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, -6.0, -5.0), ColorDBL(0.7, 0.7, 0.7)); // Hittas
	rectangles_out.push_back(wall3);

	// Walls infront of y (x, 6.0, z)
	Rectangle wall4(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(0.0, 6.0, 5.0), ColorDBL(0.0, 1.0, 0.7));
	rectangles_out.push_back(wall4);
	Rectangle wall5(glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, 6.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, 6.0, 5.0), ColorDBL(0.5, 0.5, 0.5)); // Hittas men inte först
	rectangles_out.push_back(wall5);
	Rectangle wall6(glm::vec3(10.0, 6.0, 5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(13.0, 0.0, -5.0), glm::vec3(13.0, 0.0, 5.0), ColorDBL(1.0, 0.0, 0.0)); // Hittas men inte först
	rectangles_out.push_back(wall6);

	return rectangles_out;
}

std::vector<Triangle> defineTriangles() {
	std::vector<Triangle> triangles_out;

	Triangle floorfront(glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), ColorDBL(0.4, 1.0, 0.7)); // Hittas
	triangles_out.push_back(floorfront);

	Triangle floorbehind(glm::vec3(-3.0 , 0.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(0.0, 6.0, -5.0), ColorDBL(0.3, 1.0, 0.7));
	triangles_out.push_back(floorbehind);

	Triangle roofbehind(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(0.2, 1.0, 0.7));
	triangles_out.push_back(roofbehind);

	Triangle rooffront(glm::vec3(13.0, 0.0, 5.0), glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, 6.0, 5.0), ColorDBL(0.1, 1.0, 0.7));
	triangles_out.push_back(rooffront);

	return triangles_out;
}

void printColor(std::vector<std::vector<double>>& detectedColors_in, std::vector<double> colorValues_in, glm::vec3 intersectionPoint) {
	/*bool isUnique = true;
	for (std::vector<double> c : detectedColors_in) {
		if (colorValues_in == c) {
			isUnique = false;
		}
	}
	if (isUnique) {
		ColorDBL::displayColor(colorValues_in);
		detectedColors_in.push_back(colorValues_in);

		std::string printPosition = "(" + std::to_string(intersectionPoint.x) + ", "
			+ std::to_string(intersectionPoint.y) + ", "
			+ std::to_string(intersectionPoint.z) + ")";
		std::cout << "Intersection point is: " << printPosition << "\n";
	}*/
	ColorDBL::displayColor(colorValues_in);
}

int main()
{
	std::vector<Rectangle> rectangles = defineRectangles();
	std::vector<Triangle> triangles = defineTriangles();

	Camera myCamera = Camera(800.0, 800.0);
	std::vector<std::vector<double>> detectedColors;

	std::cout << "P3" << "\n";
	std::cout << " 256 " << " 256 " << "\n";
	std::cout << "255" << "\n";

	for (double i = 0.0; i < 800.0; i++) {
		for (double j = 0.0; j < 800.0; j++) {
			Ray ray = myCamera.GetRay(i, j);
			glm::vec3 rayDirection = ray.GetRayDirection();
			std::vector<double> colorValues = { 0, 0, 0 };
			glm::vec3 intersectionPoint = {0, 0, 0};

			for (Rectangle r : rectangles) {
				double dotProduct = glm::dot(r.GetNormal(), rayDirection);
				if (dotProduct < 0.0) {
					if (ray.DoesCollide(r.GetNormal(), r.GetV(), r.GetC1(), r.GetC2())) {
						ColorDBL pixelColor = r.FetchColor();
						colorValues = pixelColor.getColor();

						intersectionPoint = ray.GetIntersectionPoint(r.GetNormal(), r.GetV());
						// Print the color of the wall where collision was detected
						// printColor(detectedColors, colorValues, intersectionPoint);
						break;
					}
				}
			}

			//for (Triangle t : triangles) {
			//	double dotProduct = glm::dot(t.GetNormal(), rayDirection);
			//	if (dotProduct < 0.0) {
			//		if (ray.DoesCollide(t.GetNormal(), t.GetV(), t.GetC1(), t.GetC2())) {
			//			ColorDBL pixelColor = t.FetchColor();
			//			colorValues = pixelColor.getColor();

			//			intersectionPoint = ray.GetIntersectionPoint(t.GetNormal(), t.GetV());
			//			// Print the color of the wall where collision was detected
			//			// printColor(detectedColors, colorValues, intersectionPoint);
			//			break;
			//		}
			//	}
			//}

			printColor(detectedColors, colorValues, intersectionPoint);
		}
	}

	return 0;


}
