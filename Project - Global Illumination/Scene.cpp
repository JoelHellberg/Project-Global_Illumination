// Project - Global Illumination.cpp : Defines the entry point for the application.
//

#include "Scene.h"
#include "CpuManagement.h"
#include <ppl.h>
#include <vector>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <concurrent_vector.h> // Include for concurrency::parallel_for, if needed

#include <mutex>
#include <atomic>

static std::mutex fakeMutex;


//Print all color in a column
void printColor(std::vector<double> colorValues_in) {

	ColorDBL::displayColor(colorValues_in);
}

void updateProgressbar(std::atomic<size_t>& pixelsDone, size_t dimensions) {
	size_t done = pixelsDone.fetch_add(1) + 1;  // Atomically increment and get the new value

	if (done % 1000 == 0) {
		size_t totalPixels = dimensions * dimensions;
		double percent = (100.0 * done) / totalPixels;

		std::lock_guard<std::mutex> lock(fakeMutex); // prevent interleaved prints
		std::cerr << "\rProgress: " << std::fixed << std::setprecision(1)
			<< percent << "% (" << done << "/" << totalPixels << ")" << std::flush;
	}
}


int main()
{
	//Vectors which saves the shapes of the scene
	std::vector<Shape*> room;

	std::vector<Rectangle> rectangles = defineRectangles();
	std::vector<Triangle> triangles = defineTriangles();

	Light LightSource(glm::vec3(0.0, 2.0, 5.0), glm::vec3(5.0, 2.0, 5.0), glm::vec3(5.0, -2.0, 5.0), glm::vec3(0.0, -2.0, 5.0), Material(ColorDBL(1.0, 1.0, 1.0), "light"));
	room.push_back(&LightSource);

	for (Rectangle& rectangle : rectangles) {
		Shape* dummy_shape = &rectangle;
		room.push_back(dummy_shape);
	}
	for (Triangle& triangle : triangles) {
		Shape* dummy_shape = &triangle;
		room.push_back(dummy_shape);
	}

	std::vector<Shape*> obstacles;

	std::vector<Rectangle> rectanglesObstacles = defineObstaclesRectangles();
	std::vector<Triangle> trianglesObstacles = defineObstaclesTriangles();

	for (Rectangle& rectangle : rectanglesObstacles) {
		Shape* dummy_shape = &rectangle;
		obstacles.push_back(dummy_shape);
	}
	for (Triangle& triangle : trianglesObstacles) {
		Shape* dummy_shape = &triangle;
		obstacles.push_back(dummy_shape);
	}

	std::vector<Sphere> spheres = defineSphere();


	// Dimension of the output image
	size_t dimensions = 200.0;
	// Factors that influence the detail of sharpness of the render
	double noSamples = 100.0;
	int maxDepth = 5;

	// Define the Camera
	Camera myCamera = Camera(dimensions, dimensions);
	
	//Std::cout for the ppm-format
	std::cout << "P3" << "\n";//ppm
	std::cout << " " << dimensions << " " << " " << dimensions << " " << "\n"; //Dimensions for the image
	std::cout << "255" << "\n"; //Define that RGB is used

	CollisionHandler myCollisionHandler(room, obstacles, spheres, LightSource, noSamples, maxDepth);

	size_t totalPixels = dimensions * dimensions;
	std::vector<std::vector<double>> pixelColors(totalPixels, { 0.0, 0.0, 0.0 });

	std::queue<std::pair<size_t, size_t>> tasks; // Queue for pixel tasks
	std::mutex queueMutex; // Mutex for thread-safe access to the queue

	// Enqueue pixel tasks
	for (size_t j = 0; j < dimensions; ++j) {
		for (size_t i = 0; i < dimensions; ++i) {
			tasks.push({ j, i });
		}
	}

	std::atomic<size_t> pixelsDone(0);

	concurrency::parallel_for(size_t(0), dimensions, [&](size_t j) {
		for (size_t i = 0; i < dimensions; i++) {
			// Check CPU usage and pause if above 80%
			// CpuManagement::WaitForCpuBelowThreshold(80.0);

			Ray ray = myCamera.GetRay(i, j);

			ColorDBL leanColor(0.0, 0.0, 0.0);
			for (int s = 0; s < noSamples; s++) {
				Material mat = myCollisionHandler.GetCollidingMaterial(ray);
				leanColor += mat.getColor();  // Accumulate the color
			}

			// Average the colors after the loop
			leanColor = leanColor / noSamples;

			// Apply gamma correction to the averaged color
			leanColor = glm::pow(leanColor.getColorGlm(), glm::vec3(1.0 / 2.2));

			// Clamp the colors
			leanColor = leanColor.ClampColors();

			// Calculate 1D index based on 2D coordinates (i, j)
			size_t index = j * dimensions + i;

			// Ensure safe access to pixelColors
			pixelColors[index] = leanColor.getColor();

			updateProgressbar(pixelsDone, dimensions);
		}
		});

	for (const std::vector<double>& color : pixelColors) {
		printColor(color);
	}


	return 0;


}
