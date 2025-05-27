#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Tuple.hpp"
#include "Ray.hpp"
#include <vector>
#include <string>

enum class ShapeType {
	Sphere,
	Undefined
};

class Shape;

typedef struct intersection
{
	double t;
	Shape *shape;
} t_intersection;

class Shape
{
	public:
		~Shape() = default;

		//getters
		Tuple getCenterPointOfShape() const;
		size_t getId() const;
		ShapeType getShapeType() const;
		virtual std::string printShapeType() const = 0;
		//setters
		void setCenterPointOfShape(const Tuple &centerPointOfShape);

		virtual std::vector<t_intersection> calculateIntersection(const Ray &ray) const = 0;
	protected:
		Shape();
		Shape(Tuple centerPointOfShape);
		Tuple centerPointOfShape;
		static size_t next_id;
		size_t id;
	protected:
		ShapeType shape_type;
};

virtual t_intersection hit(const Ray &ray) const = 0;

#endif
