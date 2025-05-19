#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iostream>
#include <stdexcept>
#include "Color.hpp"
#define MAXCOLORVALUE 255
#define WIDTH 1200
#define HEIGHT 800

class Canvas
{
	public:
	Canvas();
	Canvas(size_t width, size_t height);
	~Canvas() = default;

	//getters
	size_t getWidth() const { return (width); }
	size_t getHeight() const { return (height); }
	Color getPixel(size_t x, size_t y) const;

	//helpers
	void WritePixel(size_t x, size_t y, const Color &color);
	void WritePPM(const std::string &filename) const;

	Color **canvas;

	private:
	size_t width;
	size_t height;
};

//helper functions
void init_canvas(Canvas *canvas, size_t width, size_t height, Color color);

#endif
