#include "Color.hpp"

Color::Color() : Tuple(0, 0, 0, 0) {}

Color::Color(double r, double g, double b) : Tuple(r, g, b, 1) {}

//helper functions
Color hadamard_product(const Color &firstColor, const Color &toBlend)
{
    return (Color(firstColor.r() * toBlend.r(), firstColor.g() * toBlend.g(), firstColor.b() * toBlend.b()));
}

//overload operators
Color operator*(const Color &firstColor, double scalar)
{
    return (Color(firstColor.r() * scalar, firstColor.g() * scalar, firstColor.b() * scalar));
}

Color operator*(const Color &firstColor, const Color &other)
{
    return (Color(firstColor.r() * other.r(), firstColor.g() * other.g(), firstColor.b() * other.b()));
}

Color operator+(const Color &firstColor, const Color &other)
{
    return (Color(firstColor.r() + other.r(), firstColor.g() + other.g(), firstColor.b() + other.b()));
}

Color operator-(const Color &firstColor, const Color &other)
{
    return (Color(firstColor.r() - other.r(), firstColor.g() - other.g(), firstColor.b() - other.b()));
}
