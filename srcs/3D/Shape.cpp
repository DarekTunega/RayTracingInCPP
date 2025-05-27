#include "Shape.hpp"
#include <stdexcept>

size_t Shape::next_id = 0;

Shape::Shape() : centerPointOfShape(point(0,0,0)), id(next_id++)
{
	this->centerPointOfShape = Tuple(0,0,0,1);
	this->shape_type = ShapeType::Undefined;
}

Shape::Shape(Tuple centerPointOfShape) : centerPointOfShape(centerPointOfShape), id(next_id++)
{
	if(centerPointOfShape.getType() != TupleType::Point)
	{
		throw std::invalid_argument("Center point of shape must be a point");
	}
	this->shape_type = ShapeType::Undefined;
}

Tuple Shape::getCenterPointOfShape() const
{
	return centerPointOfShape;
}

size_t Shape::getId() const
{
	return id;
}

ShapeType Shape::getShapeType() const
{
	return shape_type;
}

void Shape::setCenterPointOfShape(const Tuple &centerPointOfShape)
{
	this->centerPointOfShape = centerPointOfShape;
}

std::string Shape::printShapeType() const
{
	return "Undefined";
}
