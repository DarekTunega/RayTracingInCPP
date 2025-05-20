#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Tuple.hpp"

class Matrix
{
	public:
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
	Matrix createInverseMatrix() const;
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
Matrix operator*(const Matrix &m, const Tuple &tuple);
Matrix operator+(const Matrix &m1, const Matrix &m2);
Matrix operator-(const Matrix &m1, const Matrix &m2);

#endif
