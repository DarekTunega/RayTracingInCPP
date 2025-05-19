#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Tuple.hpp"

class Matrix
{
	public:
	Matrix();
	Matrix(int rows, int cols, const std::vector<double> &data);
	~Matrix();

	//getters
	double getDeterminant() const;
	double getValOfPosition(int row, int col) const;
	int getRows() const;
	int getCols() const;
	Matrix getCofactorMatrix();
	Matrix getIdentityMatrix();
	Matrix getInverseMatrix();
	Matrix getTranspose();
	//setters
	void setValOfPosition(int row, int col, double value);

	//helpers
	double calculateDeterminant();
	Matrix createDuplicateMatrix() const;
	Matrix createSubmatrix(char type, int row, int col);
	Matrix createInverseMatrix() const;
	void printMatrix();

	private:
	double determinant;
	int rows;
	bool isInvertible;
	int cols;
	std::vector<double> data;
};

// overload operators
bool operator==(Matrix &m1, Matrix &m2);
Matrix operator*(Matrix &m1, Matrix &m2);
Matrix operator*(Matrix &m, Tuple &tuple);
Matrix operator+(Matrix &m1, Matrix &m2);
Matrix operator-(Matrix &m1, Matrix &m2);

#endif
