#include "Canvas.hpp"
#include <stdexcept>
#include <fstream>

Canvas::Canvas()
{
	width = WIDTH;
	height = HEIGHT;
	init_canvas(this, WIDTH, HEIGHT, Color(0, 0, 0));
}

Canvas::Canvas(size_t width, size_t height)
{
	if (width <= 0 || height <= 0)
		throw std::invalid_argument("Width and height must be positive integers");
	this->width = width;
	this->height = height;
	init_canvas(this, this->width, this->height, Color(0, 0, 0));
}

//getters
Color Canvas::getPixel(size_t x, size_t y) const
{
	if (x >= width || y >= height)
		throw std::out_of_range("Pixel coordinates out of range");
	return (canvas[y][x]);
}

//helpers
void Canvas::WritePixel(size_t x, size_t y, const Color &color)
{
	if (x >= this->getWidth() || y >= this->getHeight())
		throw std::out_of_range("Pixel coordinates out of range");
	this->canvas[y][x] = color;
}

void Canvas::WritePPM(const std::string &filename) const
{
	std::ofstream out(filename);
	if (!out)
		throw std::runtime_error("Cannot open file for writing");

	// Write PPM header
	out << "P3\n" << width << " " << height << "\n255\n";

	// Write pixel data
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			if(x % 70 == 0 && x != 0)
				out << "\n";
			Color c = canvas[y][x];
			// Clamp and scale color values to [0,255]
			int r = std::max(0, std::min(MAXCOLORVALUE, static_cast<int>(c.r() * MAXCOLORVALUE)));
			int g = std::max(0, std::min(MAXCOLORVALUE, static_cast<int>(c.g() * MAXCOLORVALUE)));
			int b = std::max(0, std::min(MAXCOLORVALUE, static_cast<int>(c.b() * MAXCOLORVALUE)));
			out << r << " " << g << " " << b << " ";
		}
		out << "\n";
	}
	out.close();
}

//helper functions
void init_canvas(Canvas *canvas, size_t width, size_t height, Color color)
{
	canvas->canvas = new Color*[height];
	for (size_t i = 0; i < height; i++)
	{
		canvas->canvas[i] = new Color[width];
		for (size_t j = 0; j < width; j++)
		{
			canvas->canvas[i][j] = color;
		}
	}
}
