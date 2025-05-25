#include <iostream>
#include "Color.hpp"
#include "Projectile.hpp"
#include "Enviroment.hpp"
#include <unistd.h>
#include "Canvas.hpp"
#include "Tuple.hpp"
#include "Matrix.hpp"
#include <ctime>
#include "Ray.hpp"

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

int getCurrentHour()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return ltm->tm_hour % 12;
}

int getCurrentMinute()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return ltm->tm_min;
}

void drawLine(Canvas &canv, size_t x1, size_t x2, size_t y1, size_t y2, const Color &color, bool thick = false)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = std::max(abs(dx), abs(dy));
	float xIncrement = static_cast<float>(dx) / steps;
	float yIncrement = static_cast<float>(dy) / steps;
	float x = x1;
	float y = y1;
	for (int i = 0; i < steps; i++)
	{
		if(thick)
		{
			canv.WritePixel(static_cast<size_t>(x), static_cast<size_t>(y), color);
			canv.WritePixel(static_cast<size_t>(x), static_cast<size_t>(y + 1), color);
			canv.WritePixel(static_cast<size_t>(x), static_cast<size_t>(y - 1), color);
		}
		else
		{
			canv.WritePixel(static_cast<size_t>(x), static_cast<size_t>(y), color);
		}
		x += xIncrement;
		y += yIncrement;
	}
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
	delete[] platno.canvas;
	for (size_t i = 0; i < platno.getHeight(); i++)
	{
		delete[] platno.canvas[i];
	}
}

void drawBigDot(Canvas &canv, size_t x, size_t y, const Color &color)
{
	canv.WritePixel(x, y, color);
	canv.WritePixel(x + 1, y, color);
	canv.WritePixel(x, y + 1, color);
	canv.WritePixel(x + 1, y + 1, color);
	canv.WritePixel(x - 1, y, color);
	canv.WritePixel(x, y - 1, color);
	canv.WritePixel(x - 1, y - 1, color);
	canv.WritePixel(x + 1, y - 1, color);
	canv.WritePixel(x - 1, y + 1, color);
}

void drawClock()
{
	Canvas canvas(900, 500);
	Color white(1, 1, 1);
	Color blue(0, 1, 1);

	int width = canvas.getWidth();
	int height = canvas.getHeight();
	Tuple center = point(width / 2.0, height / 2.0, 0);
	center.printTuple();
	size_t x = static_cast<size_t>(center.getX());
	size_t y = static_cast<size_t>(center.getY());
	drawBigDot(canvas, x, y, white);
	for (int i = 0; i < 12; i++)
	{
		Tuple hour = point(center.getX(), center.getY() - 200, 0);
		Matrix rotate = Matrix::rotateZ(i * 30);
		hour = rotate * (hour - center) + center;
		drawBigDot(canvas, static_cast<size_t>(hour.getX()), static_cast<size_t>(hour.getY()), white);
		if(getCurrentHour() == i)
			drawLine(canvas, x, static_cast<size_t>(hour.getX()), y, static_cast<size_t>(hour.getY() + 10), white, true);
	}
	for (int i = 0; i < 60; i++)
	{
		Tuple minute = point(center.getX(), center.getY() - 195, 0);
		Matrix rotate = Matrix::rotateZ(i * 6);
		minute = rotate * (minute - center) + center;
		if(i % 5 != 0)
			canvas.WritePixel(static_cast<size_t>(minute.getX()), static_cast<size_t>(minute.getY()), blue);
		if(getCurrentMinute() == i)
			drawLine(canvas, x, static_cast<size_t>(minute.getX()), y, static_cast<size_t>(minute.getY() + 15), blue, false);
	}
	canvas.WritePPM("clock.ppm");

}

int main()
{
	//TestingDrawingPixelsInPPM();
	//testingIfInvertedMatrixIsCorrect();
	drawClock();
	// std::cout << "Current hour: " << getCurrentHour() << std::endl;
	Tuple direction = vector(2,-2,4);
	 Tuple origin = point(2,3,4);
	 Tuple dir = vector(1,0,0);
	Ray aFuckingRay = Ray(origin,dir);
	Tuple newPosition = aFuckingRay.rayPosition(-1);
	newPosition.printTuple();
	return (0);
}
