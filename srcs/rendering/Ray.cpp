#include "Ray.hpp"

Ray::Ray(Tuple origin, Tuple direction)
{
	if(origin.getType() != TupleType::Point)
		throw std::invalid_argument("Passed origin is not a point!\n");
	if(direction.getType() != TupleType::Vector)
		throw std::invalid_argument("Passed direction is not a vector!\n");
	this->origin = origin;
	this->direction = direction;
}

Tuple Ray::getOrigin() const
{
	return this->origin;
}

Tuple Ray::getDirection() const
{
	return this->direction;
}

void Ray::setOrigin(const Tuple &newOrigin)
{
	this->origin = newOrigin;
}

void Ray::setDirection(const Tuple &newDirection)
{
	this->direction = newDirection;
}

Tuple Ray::rayPosition(double time) const
{
	return (this->origin + (this->direction * time));
}

Ray::Ray()
{
	Tuple origin = point(0,0,0);
	Tuple direction = vector(0,0,0);
	this->origin = origin;
	this->direction = direction;
}
