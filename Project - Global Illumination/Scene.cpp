// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include <ppl.h>


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

	Light LightSource(glm::vec3(0.0, 2.0, 5.0), glm::vec3(5.0, 2.0, 5.0), glm::vec3(5.0, -2.0, 5.0), glm::vec3(0.0, -2.0, 5.0), Material(ColorDBL(1.0, 1.0, 1.0), false, true));
	shapes.push_back(&LightSource);

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

	// Define the Camera
	Camera myCamera = Camera(dimensions, dimensions);
	
	//Std::cout for the ppm-format
	std::cout << "P3" << "\n";//ppm
	std::cout << " " << dimensions << " " << " " << dimensions << " " << "\n"; //Dimensions for the image
	std::cout << "255" << "\n"; //Define that RGB is used

	int number_of_reflections = 0;

	//concurrency::parallel_for(size_t(0), (size_t)dimensions, [&](size_t j) {
			for (double i = dimensions - 1.0; i >= 0.0; i--) {
				for (double j = dimensions - 1.0; j >= 0.0; j--) {

					Ray ray = myCamera.GetRay(j, i);

					Material mat = CollisionHandler().GetCollidingMaterial(shapes, ray, LightSource);

					/*LightSource.RandomPointOnLight();*/


					/*std::cout << "Area: " << LightSource.GetArea();*/


					// Clamp the colors
					mat.changeColor(mat.getColor().ClampColors());
					// Print the color of the wall where collision was detected
					printColor(mat.getColor().getColor());
				}
			}
		//});

	return 0;


}
