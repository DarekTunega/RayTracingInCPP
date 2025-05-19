#include "Projectile.hpp"

Projectile::Projectile()
{
    position = point(0.0, 0.0, 0.0);
    velocity = vector(0.0, 0.0, 0.0);
}

Projectile::Projectile(const Tuple &position, const Tuple &velocity)
{
    this->position = position;
    this->velocity = velocity;
}

//getters
Tuple Projectile::getPosition(void) const
{
    return (position);
}

Tuple Projectile::getVelocity(void) const
{
    return (velocity);
}

//setters
void Projectile::setPosition(const Tuple &position)
{
    this->position = position;
}

void Projectile::setVelocity(const Tuple &velocity)
{
    this->velocity = velocity;
}

//helper functions
Projectile tick(const Enviroment &env, const Projectile &proj)
{
    Tuple newPosition = proj.getPosition() + proj.getVelocity();
    Tuple newVelocity = proj.getVelocity() + env.getGravity() + env.getWind();
    return (Projectile(newPosition, newVelocity));
}