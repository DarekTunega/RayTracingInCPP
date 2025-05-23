#include <iostream>
#include "Color.hpp"
#include "Projectile.hpp"
#include "Enviroment.hpp"
#include <unistd.h>
#include "Canvas.hpp"
#include "Tuple.hpp"
#include "Matrix.hpp"

void testingIfInvertedMatrixIsCorrect()
{
	Matrix A(4,4, {3,-9,7,3,
			3,-8,2,-9,
			-4,4,4,1,
			-6,5,-1,1});

	Matrix B(4,4, {8,2,2,2,
			3,-1,7,0,
			7,0,5,4,
			6,-2,0,5});

	std::cout << "Matrix A:" << std::endl;
	A.printMatrix();
	std::cout << "--------------------------------" << std::endl;

	std::cout << "Matrix B:" << std::endl;
	B.printMatrix();
	std::cout << "--------------------------------" << std::endl;

	Matrix C = A * B;
	std::cout << "Matrix C (A * B):" << std::endl;
	C.printMatrix();
	std::cout << "--------------------------------" << std::endl;

	Matrix B_inverse = B.getInverseMatrix();
	std::cout << "Matrix B inverse:" << std::endl;
	B_inverse.printMatrix();
	std::cout << "--------------------------------" << std::endl;

	Matrix result = C * B_inverse;
	std::cout << "Result (C * B_inverse):" << std::endl;
	result.printMatrix();
	std::cout << "--------------------------------" << std::endl;

	std::cout << "Original Matrix A:" << std::endl;
	A.printMatrix();
}

void TestingDrawingPixelsInPPM()
{
	Canvas platno(900, 500);
	Color blue(0, 0, 1);
	Projectile projectile(point(0, 1, 0), vector(1, 1.8, 0).normalize() * 11.25);
	Enviroment enviroment(vector(0, -0.1, 0), vector(-0.01, 0, 0));
	int ticks = 0;
	std::cout << "Initial velocity: ";
	projectile.getVelocity().printTuple();
	std::cout << "Initial position: ";
	projectile.getPosition().printTuple();
	while (projectile.getPosition().getY() > 0)
	{
		projectile = tick(enviroment, projectile);
		std::cout << "Tick " << ticks << ": ";
		projectile.getPosition().printTuple();

		size_t x = static_cast<size_t>(projectile.getPosition().getX());
		std::cout << "X: " << x << std::endl;
		std::cout << "Y: " << projectile.getPosition().getY() << std::endl;
		size_t y = static_cast<size_t>(platno.getHeight() - projectile.getPosition().getY());
		if (x < 400 && y < 400)
		{
			platno.WritePixel(x, y, blue);
		}
		ticks++;
	}
	std::cout << "Projectile hit the ground after " << ticks << " ticks." << std::endl;
	std::cout << "Final position: ";
	projectile.getPosition().printTuple();
	std::cout << "Final velocity: ";
	projectile.getVelocity().printTuple();
	platno.WritePPM("test.ppm");
}

void translationTestToPPM() {
	// Create a canvas
	Canvas canvas(400, 400);

	// Create colors
	Color red(1, 0, 0);      // For original point
	Color green(0, 1, 0);    // For translated point
	Color blue(0, 0, 1);     // For vector

	// Create a point and a vector
	Tuple point(100, 200, 0, 1);     // A point at (100, 200)
	Tuple vector(50, 50, 0, 0);      // A vector pointing (50, 50)

	// Create translation matrix (move by 100 in x and 50 in y)
	Matrix transform = Matrix::translation(100, 50, 0);

	// Get translated point
	Tuple translatedPoint = transform * point;

	// Draw original point (red)
	canvas.WritePixel(point.getX(), canvas.getHeight() - point.getY(), red);

	// Draw translated point (green)
	canvas.WritePixel(translatedPoint.getX(), canvas.getHeight() - translatedPoint.getY(), green);

	// Draw vector as a line (blue)
	// We'll draw it from the original point
	for(int i = 0; i < 50; i++) {
		double t = i / 50.0;
		int x = point.getX() + (vector.getX() * t);
		int y = point.getY() + (vector.getY() * t);
		canvas.WritePixel(x, canvas.getHeight() - y, blue);
	}

	// Draw the same vector from the translated point (to show it doesn't change)
	for(int i = 0; i < 50; i++) {
		double t = i / 50.0;
		int x = translatedPoint.getX() + (vector.getX() * t);
		int y = translatedPoint.getY() + (vector.getY() * t);
		canvas.WritePixel(x, canvas.getHeight() - y, blue);
	}

	// Save to PPM
	canvas.WritePPM("translation_test.ppm");
	std::cout << "Translation test saved to translation_test.ppm" << std::endl;
}

void scalingTestToPPM() {
	// Create a canvas
	Canvas canvas(400, 400);

	// Create colors
	Color red(1, 0, 0);      // For original point
	Color green(0, 1, 0);    // For scaled point
	Color blue(0, 0, 1);     // For vector
	Color yellow(1, 1, 0);   // For grid lines

	// Create a point and a vector
	Tuple point(-4, 6, 0, 1);     // Original point from the test
	Tuple vector(2, 2, 0, 0);     // A vector for visualization

	// Create scaling matrix (scale by 2 in x, 3 in y)
	Matrix transform = Matrix::scaling(2, 3, 1);

	// Get scaled point
	Tuple scaledPoint = transform * point;

	// Draw grid lines for reference
	for(size_t i = 0; i < canvas.getWidth(); i += 20) {
		for(size_t j = 0; j < canvas.getHeight(); j++) {
			canvas.WritePixel(i, j, yellow);
		}
	}
	for(size_t i = 0; i < canvas.getHeight(); i += 20) {
		for(size_t j = 0; j < canvas.getWidth(); j++) {
			canvas.WritePixel(j, i, yellow);
		}
	}

	// Convert coordinates to canvas space (centering and scaling for visibility)
	// Scale factor of 20 to make it more visible
	// Add 200 to center in the 400x400 canvas
	size_t canvasX = static_cast<size_t>(point.getX() * 20 + 200);
	size_t canvasY = static_cast<size_t>(point.getY() * 20 + 200);
	size_t scaledCanvasX = static_cast<size_t>(scaledPoint.getX() * 20 + 200);
	size_t scaledCanvasY = static_cast<size_t>(scaledPoint.getY() * 20 + 200);

	// Draw original point (red) as a small cross
	if (canvasX < canvas.getWidth() && canvasY < canvas.getHeight()) {
		for(int i = -2; i <= 2; i++) {
			for(int j = -2; j <= 2; j++) {
				if(canvasX + i < canvas.getWidth() && canvasY + j < canvas.getHeight()) {
					canvas.WritePixel(canvasX + i, canvas.getHeight() - (canvasY + j), red);
				}
			}
		}
	}

	// Draw scaled point (green) as a small cross
	if (scaledCanvasX < canvas.getWidth() && scaledCanvasY < canvas.getHeight()) {
		for(int i = -2; i <= 2; i++) {
			for(int j = -2; j <= 2; j++) {
				if(scaledCanvasX + i < canvas.getWidth() && scaledCanvasY + j < canvas.getHeight()) {
					canvas.WritePixel(scaledCanvasX + i, canvas.getHeight() - (scaledCanvasY + j), green);
				}
			}
		}
	}

	// Draw vector as a line (blue)
	// We'll draw it from the original point
	for(int i = 0; i < 30; i++) {
		double t = i / 30.0;
		size_t x = static_cast<size_t>(canvasX + (vector.getX() * 20 * t));
		size_t y = static_cast<size_t>(canvasY + (vector.getY() * 20 * t));
		if (x < canvas.getWidth() && y < canvas.getHeight()) {
			canvas.WritePixel(x, canvas.getHeight() - y, blue);
		}
	}

	// Draw the scaled vector from the scaled point
	for(int i = 0; i < 30; i++) {
		double t = i / 30.0;
		size_t x = static_cast<size_t>(scaledCanvasX + (vector.getX() * 20 * t));
		size_t y = static_cast<size_t>(scaledCanvasY + (vector.getY() * 20 * t));
		if (x < canvas.getWidth() && y < canvas.getHeight()) {
			canvas.WritePixel(x, canvas.getHeight() - y, blue);
		}
	}

	// Save to PPM
	canvas.WritePPM("scaling_test.ppm");
	std::cout << "Scaling test saved to scaling_test.ppm" << std::endl;

	// Print the actual coordinates to verify the test
	std::cout << "Original point: (" << point.getX() << ", " << point.getY() << ")" << std::endl;
	std::cout << "Scaled point: (" << scaledPoint.getX() << ", " << scaledPoint.getY() << ")" << std::endl;
}

int main()
{
	//TestingDrawingPixelsInPPM();
	//testingIfInvertedMatrixIsCorrect();
	//translationTestToPPM();
	scalingTestToPPM();
	return (0);
}
