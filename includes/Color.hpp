#ifndef COLOR_HPP
#define COLOR_HPP

#include "Tuple.hpp"

class Color : public Tuple
{
    public:
    Color();
    Color(double r, double g, double b);
    ~Color() = default;
    
    //getters
    double r() const { return (getX()); }
    double g() const { return (getY()); }
    double b() const { return (getZ()); }
};

// helper functions
Color hadamard_product(const Color &firstColor, const Color &toBlend);

// overload operators
Color operator*(const Color &firstColor, const Color &other);
Color operator*(const Color &firstColor, double scalar);
Color operator+(const Color &firstColor, const Color &other);
Color operator-(const Color &firstColor, const Color &other);

#endif