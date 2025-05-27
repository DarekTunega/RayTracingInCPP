#ifndef TUPLE_HPP
#define TUPLE_HPP
#include <cmath>
#include <iostream>


constexpr double EPSILON = 0.00001;
enum class TupleType {
	Point,
	Vector
};

class Tuple
{
	public:
	Tuple();
	Tuple(double x, double y, double z, double w);

	//getters
	double getX(void) const;
	double getY(void) const;
	double getZ(void) const;
	double getW(void) const;
	double getByIndex(int index) const;
	double getMagnitude(void) const;
	TupleType getType(void) const;

	//setters
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setW(double w);

	//helpers
	void printTuple(void) const;
	double dot(const Tuple &otherTuple) const;
	Tuple normalize(void) const;
	Tuple cross(const Tuple &otherTuple) const; // basically a "kolmice"


	~Tuple() = default;

	private:
	double x;
	double y;
	double z;
	double w;
	TupleType type;
	void setType(TupleType type);

	protected:

};

// kinda constructors
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);




// comparison functions
bool areDoublesEqual(const double &a,const double &b);

// overload operators
bool operator==(const Tuple &a, const Tuple &b);

Tuple operator+(const Tuple &a, const Tuple &b);

Tuple operator-(const Tuple &a, const Tuple &b);

Tuple operator-(const Tuple &a);

Tuple operator*(const Tuple &a, const double &b);



#endif
