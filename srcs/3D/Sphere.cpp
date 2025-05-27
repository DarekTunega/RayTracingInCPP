#include "Sphere.hpp"
#include <stdexcept>

Sphere::Sphere(Tuple centerPointOfShape, double radius) : Shape(centerPointOfShape), radius(radius)
{
	if(radius <= 0)
	{
		throw std::invalid_argument("Radius must be positive");
	}
	this->shape_type = ShapeType::Sphere;
}

double Sphere::getRadius() const
{
	return radius;
}

void Sphere::setRadius(double radius)
{
	this->radius = radius;
}

std::string Sphere::printShapeType() const
{
	return "Sphere";
}

std::vector<t_intersection> Sphere::calculateIntersection(const Ray& ray) const
{
	std::vector<t_intersection> intersections;
	Tuple sphereToRay = ray.getOrigin() - this->getCenterPointOfShape();
	double a = ray.getDirection().dot(ray.getDirection());
	double b = 2 * ray.getDirection().dot(sphereToRay);
	double c = sphereToRay.dot(sphereToRay) - this->getRadius() * this->getRadius();
	double discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return intersections;
	double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	t_intersection i1 = {t1, const_cast<Sphere*>(this)};
	t_intersection i2 = {t2, const_cast<Sphere*>(this)};
	intersections.push_back(i1);
	intersections.push_back(i2);

	return intersections;
}
