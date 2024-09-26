// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"

#include "ColorDBL.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Camera.h"
#include "Ray.h"

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

	//Triangle floorfront1(glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), ColorDBL(1.0, 1.0, 0.0)); // Hittas
	//triangles_out.push_back(floorfront1);
	//Triangle floorfront2(glm::vec3(13.0, 0.0, -5.0), glm::vec3(10.0, 6.0, -5.0), glm::vec3(10.0, -6.0, -5.0), ColorDBL(1.0, 1.0, 0.0)); // Hittas
	//triangles_out.push_back(floorfront2);

	/*Triangle floorbehind(glm::vec3(-3.0, 0.0, -5.0), glm::vec3(0.0, -6.0, -5.0), glm::vec3(0.0, 6.0, -5.0), ColorDBL(0.3, 1.0, 0.7));
	triangles_out.push_back(floorbehind);*/

	/*Triangle roofbehind(glm::vec3(-3.0, 0.0, 5.0), glm::vec3(0.0, 6.0, 5.0), glm::vec3(0.0, -6.0, 5.0), ColorDBL(0.0, 8.0, 0.0));
	triangles_out.push_back(roofbehind);*/

	Triangle rooffront1(glm::vec3(10.0, 0.0, 5.0), glm::vec3(10.0, 6.0, 5.0), glm::vec3(13.0, 0.0, 5.0), ColorDBL(0.1, 1.0, 0.7));
	triangles_out.push_back(rooffront1);
	Triangle rooffront2(glm::vec3(10.0, -6.0, 5.0), glm::vec3(10.0, 0.0, 5.0), glm::vec3(13.0, 0.0, 5.0), ColorDBL(0.1, 1.0, 0.7));
	triangles_out.push_back(rooffront2);

	return triangles_out;
}

void printColor(std::vector<std::vector<double>>& detectedColors_in, std::vector<double> colorValues_in, std::vector<int>& occurences_in) {
	//bool isUnique = true;

	//for (int i = 0; i < detectedColors_in.size(); i++) {
	//	if (colorValues_in == detectedColors_in[i]) {
	//		occurences_in[i] = occurences_in[i] + 1;
	//		isUnique = false;
	//	}
	//}

	//if (isUnique) {
	//	// ColorDBL::displayColor(colorValues_in);
	//	detectedColors_in.push_back(colorValues_in);
	//	occurences_in.push_back(1);
	//}
	ColorDBL::displayColor(colorValues_in);
}

int main()
{
	std::vector<Rectangle> rectangles = defineRectangles();
	std::vector<Triangle> triangles = defineTriangles();

	double dimensions = 800.0;
	Camera myCamera = Camera(dimensions, dimensions);
	std::vector<std::vector<double>> detectedColors;
	std::vector<int> occurences;

	std::cout << "P3" << "\n";
	std::cout << " " << dimensions << " " << " " << dimensions << " " << "\n";
	std::cout << "255" << "\n";
	int columns = 0;

	for (double i = dimensions - 1.0; i >= 0.0; i--) {
		for (double j = dimensions - 1.0; j >= 0.0; j--) {

			Ray ray = myCamera.GetRay(j, i);
			std::vector<double> colorValues = { 0, 0, 0 };
			glm::vec3 intersectionPoint = {0, 0, 0};

			for (Rectangle rectangle : rectangles) {
				double dotProduct = glm::dot(rectangle.GetNormal(), ray.GetRayDirection());
				if (dotProduct < 0.0) {
					if (rectangle.DoesCollide(ray)) {
						ColorDBL pixelColor = rectangle.FetchColor();
						colorValues = pixelColor.getColor();

						intersectionPoint = rectangle.GetIntersectionPoint(ray);
						break;
					}
				}
			}

			for (Triangle triangle : triangles) {
				double dotProduct = glm::dot(triangle.GetNormal(), ray.GetRayDirection());
				if (dotProduct < 0.0) {
					if (triangle.DoesCollide(ray)) {
						ColorDBL pixelColor = triangle.FetchColor();
						colorValues = pixelColor.getColor();

						intersectionPoint = triangle.GetIntersectionPoint(ray);
						break;
					}
				}
			}

			// Print the color of the wall where collision was detected
			printColor(detectedColors, colorValues, occurences);
		}
	}

	/*for (int i = 0; i < detectedColors.size(); i++) {
		ColorDBL::displayColor(detectedColors[i]);
		std::cout << "number of occurences: " << occurences[i] << "\n\n";
	}*/

	return 0;


}
