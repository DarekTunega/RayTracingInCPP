#include "Matrix.hpp"
#include <stdexcept>

Matrix Matrix::translation(double x, double y, double z)
{
	std::vector<double> data =
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return Matrix(4, 4, data);
}

Matrix Matrix::scaling(double x, double y, double z)
{
	std::vector<double> data =
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
	return Matrix(4, 4, data);
}

Matrix Matrix::rotateX(double degrees)
{
	double radians = toRadians(degrees);
	std::vector<double> data =
	{
		1, 0, 0, 0,
		0, cos(radians), -sin(radians), 0,
		0, sin(radians), cos(radians), 0,
		0, 0, 0, 1
	};
	return Matrix(4, 4, data);
}

Matrix Matrix::rotateY(double degrees)
{
	double radians = toRadians(degrees);
	std::vector<double> data =
	{
		cos(radians), 0, sin(radians),0,
		0,			  1, 0,			  0,
		-sin(radians),0, cos(radians),0,
		0,			  0, 0,			  1
	};
	return Matrix(4, 4, data);
}

Matrix Matrix::rotateZ(double degrees)
{
	double radians = toRadians(degrees);
	std::vector<double> data =
	{
		cos(radians), -sin(radians), 0, 0,
		sin(radians), cos(radians),  0, 0,
		0,			  0,			 1, 0,
		0,			  0,			 0, 1
	};
	return Matrix(4, 4, data);
}

Matrix Matrix::shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
	std::vector<double> data =
	{
		1, xy, xz, 0,
		yx, 1, yz, 0,
		zx, zy, 1, 0,
		0, 0, 0, 1
	};
	return Matrix(4, 4, data);
}
//default constructor

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

Matrix Matrix::getCofactorMatrix() const
{
	if (rows != cols)
		throw std::invalid_argument("Cofactor matrix is only defined for square matrices");

	Matrix temp(rows, cols, std::vector<double>(rows * cols, 0));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Matrix sub = createSubmatrix('A', i, j);
			double minor = sub.calculateDeterminant();
			double cofactor = pow(-1, i + j) * minor;
			temp.setValOfPosition(i, j, cofactor);
		}
	}
	Matrix result = temp.createDuplicateMatrix();
	return (result);
}

Matrix Matrix::getIdentityMatrix() const
{
	Matrix temp(rows, cols, std::vector<double>(rows * cols, 0));
	for (int i = 0; i < rows; i++)
		temp.setValOfPosition(i, i, 1);
	Matrix result = temp.createDuplicateMatrix();
	return (result);
}

Matrix Matrix::getInverseMatrix() const
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

Matrix Matrix::getTranspose() const
{
	Matrix temp(cols, rows, std::vector<double>(cols * rows, 0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp.setValOfPosition(j, i, getValOfPosition(i, j));
	Matrix result = temp.createDuplicateMatrix();
	return (result);
}

//setters
void Matrix::setValOfPosition(int row, int col, double value)
{
	data[row * cols + col] = value;
}

//helpers
double Matrix::calculateDeterminant() const
{
	if (rows != cols) {
		throw std::invalid_argument("Cannot calculate determinant of non-square matrix");
		return (0);
	}
	if (rows == 1) {
		return (data[0]);
	}
	if (rows == 2) {
		return (data[0] * data[3] - data[1] * data[2]);
	}
	double result = 0;
	for (int j = 0; j < cols; j++) {
		Matrix sub = createSubmatrix('A', 0, j);
		double cofactor = data[j] * pow(-1, j) * sub.calculateDeterminant();
		result += cofactor;
	}
	return (result);
}

Matrix Matrix::createDuplicateMatrix() const
{
	return (Matrix(rows, cols, data));
}

Matrix Matrix::createSubmatrix(char type, int row, int col) const
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

double toRadians(double degrees)
{
	return (degrees * PI / 180);
}

double toDegrees(double radians)
{
	return (radians * 180 / PI);
}

//overload operators
bool operator==(const Matrix& m1, const Matrix& m2)
{
	if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
		return (false);
	for (int i = 0; i < m1.getRows(); i++)
		for (int j = 0; j < m1.getCols(); j++)
			if (m1.getValOfPosition(i, j) != m2.getValOfPosition(i, j))
				return (false);
	return (true);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
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

Tuple operator*(const Matrix& m, const Tuple& tuple)
{
	if (m.getCols() != 4)
		throw std::invalid_argument("Cannot multiply matrix with tuple of incompatible size");
	double x = 0, y = 0, z = 0, w = 0;
	for (int i = 0; i < m.getRows(); i++) {
		for (int j = 0; j < m.getCols(); j++) {
			double val = m.getValOfPosition(i, j) * tuple.getByIndex(j);
			switch(i) {
				case 0: x += val; break;
				case 1: y += val; break;
				case 2: z += val; break;
				case 3: w += val; break;
			}
		}
	}
	if (w == 1.0)
		return (point(x, y, z));
	else
		return (vector(x, y, z));
}

