#include <iostream>
#include "Color.hpp"
#include "Projectile.hpp"
#include "Enviroment.hpp"
#include <unistd.h>
#include "Canvas.hpp"
#include "Tuple.hpp"
#include "Matrix.hpp"

int main()
{
    // Canvas platno(900, 500);
    // Color blue(0, 0, 1);
    // Projectile projectile(point(0, 1, 0), vector(1, 1.8, 0).normalize() * 11.25);
    // Enviroment enviroment(vector(0, -0.1, 0), vector(-0.01, 0, 0));
    // int ticks = 0;
    // std::cout << "Initial velocity: ";
    // projectile.getVelocity().printTuple();
    // std::cout << "Initial position: ";
    // projectile.getPosition().printTuple();
    // while (projectile.getPosition().getY() > 0)
    // {
    //     projectile = tick(enviroment, projectile);
    //     std::cout << "Tick " << ticks << ": ";
    //     projectile.getPosition().printTuple();
        
    //     size_t x = static_cast<size_t>(projectile.getPosition().getX());
    //     std::cout << "X: " << x << std::endl;
    //     std::cout << "Y: " << projectile.getPosition().getY() << std::endl;
    //     size_t y = static_cast<size_t>(platno.getHeight() - projectile.getPosition().getY());
    //     if (x < 400 && y < 400)
    //     {
    //         platno.WritePixel(x, y, blue);
    //     }
    //     ticks++;
    // }
    // std::cout << "Projectile hit the ground after " << ticks << " ticks." << std::endl;
    // std::cout << "Final position: ";
    // projectile.getPosition().printTuple();
    // std::cout << "Final velocity: ";
    // projectile.getVelocity().printTuple();
    // platno.WritePPM("test.ppm");
    Matrix m1(4,4,{-6,1,1,6,
                -8,5,8,6,
                -1,0,8,2,
                -7,1,-1,1});
    m1 = m1.createSubmatrix('A',2,1);
    m1.printMatrix();
    return (0);  
}