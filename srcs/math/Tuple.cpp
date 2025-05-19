#include "Tuple.hpp"

Tuple::Tuple()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
	type = TupleType::Vector;
}

Tuple::Tuple(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	if(w == 1.0 || w == 1)
	{
		this->type = TupleType::Point;
		this->w = 1.0;
	}
	else if(w == 0.0 || w == 0)
	{
		this->type = TupleType::Vector;
		this->w = 0.0;
	}
	else
		throw std::invalid_argument("W index of tuple does not exist.");
}

//getters
double Tuple::getX(void) const
{
	return (x);
}

double Tuple::getY(void) const
{
	return (y);
}

double Tuple::getZ(void) const
{
	return (z);
}

double Tuple::getW(void) const
{
	return (w);
}

double Tuple::getByIndex(int index) const
{
	switch (index)
	{
		case 0:
			return (getX());
		case 1:
			return (getY());
		case 2:
			return (getZ());
		case 3:
			return (getW());
		default:
			throw std::invalid_argument("Index out of bounds");
	}
}

double Tuple::getMagnitude(void) const
{
	return (std::sqrt(x * x + y * y + z * z + w * w));
}

TupleType Tuple::getType(void) const
{
	return (type);
}

//setters
void Tuple::setX(double x)
{
	this->x = x;
}

void Tuple::setY(double y)
{
	this->y = y;
}

void Tuple::setZ(double z)
{
	this->z = z;
}

void Tuple::setType(TupleType newType)
{
	this->type = newType;
	if (newType == TupleType::Point)
		this->w = 1.0;
	else if (newType == TupleType::Vector)
		this->w = 0.0;
	else
		throw std::invalid_argument("Tuple type does not exist.");
}

void Tuple::setW(double newW)
{
	if(newW == 1.0 || newW == 1)
	{
		this->type = TupleType::Point;
		this->w = 1.0;
	}
	else if(newW == 0.0 || newW == 0)
	{
		this->type = TupleType::Vector;
		this->w = 0.0;
	}
	else
		throw std::invalid_argument("W index of tuple does not exist.");
}

//helpers
void Tuple::printTuple(void) const
{
	std::cout << "Tuple: (" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}

Tuple Tuple::normalize(void) const
{
	double magnitude = this->getMagnitude();
	if (magnitude == 0)
		return (*this);
	return (Tuple(this->getX() / magnitude, this->getY() / magnitude, this->getZ() / magnitude, this->getW() / magnitude));
}

double Tuple::dot(const Tuple &otherTuple) const
{
	return (this->getX() * otherTuple.getX() +
		this->getY() * otherTuple.getY() +
		this->getZ() * otherTuple.getZ() +
		this->getW() * otherTuple.getW());
}

Tuple Tuple::cross(const Tuple &otherTuple) const
{
	return (vector(this->getY() * otherTuple.getZ() - this->getZ() * otherTuple.getY(),
		this->getZ() * otherTuple.getX() - this->getX() * otherTuple.getZ(),
		this->getX() * otherTuple.getY() - this->getY() * otherTuple.getX()));
}

//kinda constructors
Tuple vector(double x, double y, double z)
{
	Tuple vector;
	vector.setX(x);
	vector.setY(y);
	vector.setZ(z);
	vector.setW(0.0);
	vector.setType(TupleType::Vector);
	return (vector);
}

Tuple point(double x, double y, double z)
{
	Tuple point;
	point.setX(x);
	point.setY(y);
	point.setZ(z);
	point.setW(1.0);
	point.setType(TupleType::Point);
	return (point);
}

// comparison functions
bool areDoublesEqual(const double &a, const double &b)
{
	if(fabs(a - b) < EPSILON)
		return (true);
	return (false);
}

// overload operators
Tuple operator+(const Tuple &a, const Tuple &b)
{
	return (Tuple(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ(), a.getW() + b.getW()));
}

Tuple operator-(const Tuple &a, const Tuple &b)
{
	return (Tuple(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ(), a.getW() - b.getW()));
}

Tuple operator*(const Tuple &a, const double &b)
{
	return (Tuple(a.getX() * b, a.getY() * b, a.getZ() * b, a.getW() * b));
}

Tuple operator-(const Tuple &a)
{
	return (Tuple(-a.getX(), -a.getY(), -a.getZ(), -a.getW()));
}

bool operator==(const Tuple &a, const Tuple &b)
{
	return (areDoublesEqual(a.getX(), b.getX()) &&
		areDoublesEqual(a.getY(), b.getY()) &&
		areDoublesEqual(a.getZ(), b.getZ()) &&
		areDoublesEqual(a.getW(), b.getW()));
}
