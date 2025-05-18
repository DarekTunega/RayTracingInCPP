#ifndef ENVIROMENT_HPP
#define ENVIROMENT_HPP

#include "Tuple.hpp"
#include "Projectile.hpp"
#include <stdexcept>
#define GRAVITY vector(0.0, -9.8, 0.0)

class Enviroment
{
    public:
        Enviroment();
        Enviroment(const Tuple &gravity, const Tuple &wind);
        ~Enviroment() = default;
        
        //getters
        Tuple getGravity() const { return (gravity); }
        Tuple getWind() const { return (wind); }

        
    private:
        Tuple gravity;
        Tuple wind;
};

#endif