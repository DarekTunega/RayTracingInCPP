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
	static Matrix rotation(double xRot, double yRot, double zRot);
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

// overload operators
bool operator==(const Matrix &m1, const Matrix &m2);
Matrix operator*(const Matrix &m1, const Matrix &m2);
Tuple operator*(const Matrix &m, const Tuple &tuple);
Matrix operator+(const Matrix &m1, const Matrix &m2);
Matrix operator-(const Matrix &m1, const Matrix &m2);

#endif
