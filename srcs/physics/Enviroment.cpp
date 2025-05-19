#include "Enviroment.hpp"

Enviroment::Enviroment()
{
	gravity = vector(0.0, -9.8, 0.0);
	wind = vector(0.0, 0.0, 0.0);
}

Enviroment::Enviroment(const Tuple &gravity, const Tuple &wind)
{
	if(gravity.getType() != TupleType::Vector || gravity.getW() != 0.0)
		throw std::invalid_argument("Gravity must be a vector");
	if(wind.getType() != TupleType::Vector || wind.getW() != 0.0)
		throw std::invalid_argument("Wind must be a vector");
	this->gravity = gravity;
	this->wind = wind;
}
