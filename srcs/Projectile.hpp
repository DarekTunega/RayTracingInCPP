#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Tuple.hpp"
#include "Enviroment.hpp"

class Enviroment;

class Projectile
{
    public:
        Projectile();
        Projectile(const Tuple &position, const Tuple &velocity);
        ~Projectile() = default;
        
        // getters
        Tuple getPosition(void) const;
        Tuple getVelocity(void) const;

        // setters
        void setPosition(const Tuple &position);
        void setVelocity(const Tuple &velocity);

        Tuple position;

    private:
        Tuple velocity;
};

// helper functions
Projectile tick(const Enviroment &env, const Projectile &proj);

#endif