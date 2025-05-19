#include <iostream>
#include "Color.hpp"
#include "Projectile.hpp"
#include "Enviroment.hpp"
#include <unistd.h>
#include "Canvas.hpp"
#include "Tuple.hpp"
#include "Matrix.hpp"

void testingIfInvertedMatrixIsCorrect()
{
        Matrix A(4,4, {3,-9,7,3,
                   3,-8,2,-9,
                   -4,4,4,1,
                   -6,5,-1,1});
    
    Matrix B(4,4, {8,2,2,2,
                   3,-1,7,0,
                   7,0,5,4,
                   6,-2,0,5});
    
    std::cout << "Matrix A:" << std::endl;
    A.printMatrix();
    std::cout << "--------------------------------" << std::endl;
    
    std::cout << "Matrix B:" << std::endl;
    B.printMatrix();
    std::cout << "--------------------------------" << std::endl;
    
    Matrix C = A * B;
    std::cout << "Matrix C (A * B):" << std::endl;
    C.printMatrix();
    std::cout << "--------------------------------" << std::endl;
    
    Matrix B_inverse = B.getInverseMatrix();
    std::cout << "Matrix B inverse:" << std::endl;
    B_inverse.printMatrix();
    std::cout << "--------------------------------" << std::endl;
    
    Matrix result = C * B_inverse;
    std::cout << "Result (C * B_inverse):" << std::endl;
    result.printMatrix();
    std::cout << "--------------------------------" << std::endl;
    
    std::cout << "Original Matrix A:" << std::endl;
    A.printMatrix();
}

void TestingDrawingPixelsInPPM()
{
        Canvas platno(900, 500);
    Color blue(0, 0, 1);
    Projectile projectile(point(0, 1, 0), vector(1, 1.8, 0).normalize() * 11.25);
    Enviroment enviroment(vector(0, -0.1, 0), vector(-0.01, 0, 0));
    int ticks = 0;
    std::cout << "Initial velocity: ";
    projectile.getVelocity().printTuple();
    std::cout << "Initial position: ";
    projectile.getPosition().printTuple();
    while (projectile.getPosition().getY() > 0)
    {
        projectile = tick(enviroment, projectile);
        std::cout << "Tick " << ticks << ": ";
        projectile.getPosition().printTuple();
        
        size_t x = static_cast<size_t>(projectile.getPosition().getX());
        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << projectile.getPosition().getY() << std::endl;
        size_t y = static_cast<size_t>(platno.getHeight() - projectile.getPosition().getY());
        if (x < 400 && y < 400)
        {
            platno.WritePixel(x, y, blue);
        }
        ticks++;
    }
    std::cout << "Projectile hit the ground after " << ticks << " ticks." << std::endl;
    std::cout << "Final position: ";
    projectile.getPosition().printTuple();
    std::cout << "Final velocity: ";
    projectile.getVelocity().printTuple();
    platno.WritePPM("test.ppm");
}

int main()
{
    TestingDrawingPixelsInPPM();
    testingIfInvertedMatrixIsCorrect();
    return (0);
}