// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"

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
