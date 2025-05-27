#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"

class Sphere : public Shape
{
	public:
		Sphere(Tuple centerPointOfShape, double radius);
		~Sphere() = default;

		//getters
		double getRadius() const;
		virtual std::vector<t_intersection> calculateIntersection(const Ray &ray) const override;
		virtual std::string printShapeType() const override;
		//setters
		void setRadius(double radius);

	private:
		double radius;
};

#endif
