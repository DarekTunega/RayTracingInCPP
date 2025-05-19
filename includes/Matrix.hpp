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
    Matrix getIdentityMatrix();
    Matrix getTranspose();

    //setters
    void setValOfPosition(int row, int col, double value);

    //helpers
    double calculateDeterminant();
    Matrix createSubmatrix(char type, int row, int col);
    void printMatrix();

    private:
    double determinant;
    int rows;
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