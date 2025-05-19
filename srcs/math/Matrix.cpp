#include "Matrix.hpp"
#include <stdexcept>

Matrix::Matrix()
{
    this->rows = 0;
    this->cols = 0;
    this->data = std::vector<double>();
}

Matrix::Matrix(int rows, int cols, const std::vector<double> &data)
{
    this->rows = rows;
    this->cols = cols;
    this->data = data;
    if (rows == cols)
    {
        this->determinant = calculateDeterminant();
    }
    if (determinant != 0)
        isInvertible = true;
    else
        isInvertible = false;
}

Matrix::~Matrix()
{
    this->data.clear();
}

//getters
double Matrix::getDeterminant() const
{
    return (determinant);
}

double Matrix::getValOfPosition(int row, int col) const
{
    return (data[row * cols + col]);
}

int Matrix::getRows() const
{
    return (rows);
}

int Matrix::getCols() const
{
    return (cols);
}

Matrix Matrix::getCofactorMatrix() {
    if (rows != cols)
        throw std::invalid_argument("Cofactor matrix is only defined for square matrices");

    Matrix result(rows, cols, std::vector<double>(rows * cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix sub = createSubmatrix('A', i, j);
            double minor = sub.calculateDeterminant();
            double cofactor = pow(-1, i + j) * minor;
            result.setValOfPosition(i, j, cofactor);
        }
    }
    return result;
}

Matrix Matrix::getIdentityMatrix()
{
    Matrix result(rows, cols, std::vector<double>(rows * cols, 0));
    for (int i = 0; i < rows; i++)
        result.setValOfPosition(i, i, 1);
    return (result);
}

Matrix Matrix::getInverseMatrix()
{
    if(!isInvertible)
        throw std::invalid_argument("Matrix is not invertible");
   double determinant = calculateDeterminant();
    Matrix cofactorMatrix = getCofactorMatrix();
    Matrix adjugate = cofactorMatrix.getTranspose();
    Matrix result(rows, cols, std::vector<double>(rows * cols, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.setValOfPosition(i, j, adjugate.getValOfPosition(i, j) / determinant);
    
    return (result);
}

Matrix Matrix::getTranspose()
{
    Matrix result(cols, rows, std::vector<double>(cols * rows, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.setValOfPosition(j, i, getValOfPosition(i, j));
    return (result);
}



//setters
void Matrix::setValOfPosition(int row, int col, double value)
{
    data[row * cols + col] = value;
}

//helpers
double Matrix::calculateDeterminant()
{
    if (rows != cols) {
        throw std::invalid_argument("Cannot calculate determinant of non-square matrix");
        determinant = 0;
        return (determinant);
    }
    if (rows == 1) {
        determinant = data[0];
        return (determinant);
    }
    if (rows == 2) {
        determinant = data[0] * data[3] - data[1] * data[2];
        return (determinant);
    }
    double result = 0;
    for (int j = 0; j < cols; j++) {
        Matrix sub = createSubmatrix('A', 0, j);
        double cofactor = data[j] * pow(-1, j) * sub.calculateDeterminant();
        result += cofactor;
    }
    determinant = result;
    return (determinant);
}

Matrix Matrix::createSubmatrix(char type, int row, int col)
{
    if (type == 'A')
    {
        std::vector<double> submatrix((rows - 1) * (cols - 1));
        int sub_index = 0;
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (r != row && c != col)
                {
                    submatrix[sub_index++] = data[r * cols + c];
                }
            }
        }
        return (Matrix(rows - 1, cols - 1, submatrix));
    }
    else
    {
        throw std::invalid_argument("Invalid type for subMatrix");
    }
}

void Matrix::printMatrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << this->getValOfPosition(i, j) << " ";
        std::cout << std::endl;
    }
}

//overload operators
bool operator==(Matrix& m1, Matrix& m2)
{
    if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
        return false;
    for (int i = 0; i < m1.getRows(); i++)
        for (int j = 0; j < m1.getCols(); j++)
            if (m1.getValOfPosition(i, j) != m2.getValOfPosition(i, j))
                return false;
    return true;
}

Matrix operator*(Matrix& m1, Matrix& m2)
{
    if (m1.getCols() != m2.getRows())
        throw std::invalid_argument("Cannot multiply matrices of incompatible sizes");
    Matrix result(m1.getRows(), m2.getCols(), std::vector<double>(m1.getRows() * m2.getCols(), 0));
    for (int i = 0; i < m1.getRows(); i++)
        for (int j = 0; j < m2.getCols(); j++)
            for (int k = 0; k < m1.getCols(); k++)
                result.setValOfPosition(i, j, result.getValOfPosition(i, j) + m1.getValOfPosition(i, k) * m2.getValOfPosition(k, j));
    return (result);
}

Matrix operator*(Matrix& m, Tuple& tuple)
{
    if (m.getCols() != 4)
        throw std::invalid_argument("Cannot multiply matrix with tuple of incompatible size");
    Matrix result(m.getRows(), 1, std::vector<double>(m.getRows(), 0));
    for (int i = 0; i < m.getRows(); i++)
        for (int j = 0; j < m.getCols(); j++)
            result.setValOfPosition(i, 0, result.getValOfPosition(i, 0) + m.getValOfPosition(i, j) * tuple.getByIndex(j));
    return (result);
}