#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Tuple.hpp"

constexpr double PI = 3.14159265358979323846;

class Matrix
{
	public:
	static Matrix translation(double x, double y, double z);
	static Matrix scaling(double x, double y, double z);
	static Matrix rotateX(double degrees);
	static Matrix rotateY(double degrees);
	static Matrix rotateZ(double degrees);
	static Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy);
	Matrix(int rows, int cols, const std::vector<double> &data);
	~Matrix();



	//getters
	double getDeterminant() const;
	double getValOfPosition(int row, int col) const;
	int getRows() const;
	int getCols() const;
	Matrix getCofactorMatrix() const;
	Matrix getIdentityMatrix() const;
	Matrix getInverseMatrix() const;
	Matrix getTranspose() const;
	//setters
	void setValOfPosition(int row, int col, double value);

	//helpers
	double calculateDeterminant() const;
	Matrix createDuplicateMatrix() const;
	Matrix createSubmatrix(char type, int row, int col) const;
	void printMatrix();

	private:
	Matrix();
	double determinant;
	int rows;
	int hehe;
	bool isInvertible;
	int cols;
	std::vector<double> data;
};

// helper functions
double toRadians(double degrees);
double toDegrees(double radians);

// overload operators
bool operator==(const Matrix &m1, const Matrix &m2);
Matrix operator*(const Matrix &m1, const Matrix &m2);
Tuple operator*(const Matrix &m, const Tuple &tuple);
Matrix operator+(const Matrix &m1, const Matrix &m2);
Matrix operator-(const Matrix &m1, const Matrix &m2);

#endif
