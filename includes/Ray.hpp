#ifndef RAY_HPP
#define RAY_HPP
#include "Tuple.hpp"

class Ray
{
	public:
	Ray(Tuple origin, Tuple direction);
	~Ray() = default;

	Tuple getOrigin() const;
	Tuple getDirection() const;

	void setOrigin(const Tuple &origin);
	void setDirection(const Tuple &direction);

	Tuple rayPosition(double time) const;

	private:
	Ray();
	Tuple origin;
	Tuple direction;
};

#endif
