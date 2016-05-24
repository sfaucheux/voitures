#include "sphere.h"

#include "../glm/gtx/norm.hpp"
#include "collisions.h"

using namespace std;
using namespace glm;

Sphere::Sphere(float radius)
{
    m_radius = radius;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius() const
{
    return m_radius;
}

bool Sphere::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Sphere::collide(const Sphere *s) const
{
    return Collisions::collide(this, s);
}

bool Sphere::collide(const Box* b) const
{
    return Collisions::collide(this, b);
}

bool Sphere::collide(const Mesh* m) const
{
    return Collisions::collide(this, m);
}

Contact* Sphere::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

Contact* Sphere::collisionPoints(const Sphere* s) const
{
    return Collisions::collisionPoints(this, s);
}

Contact* Sphere::collisionPoints(const Box* b) const
{
    return Collisions::collisionPoints(this, b);
}

Contact* Sphere::collisionPoints(const Mesh* m) const
{
    return Collisions::collisionPoints(this, m);
}
AABB Sphere::getAABB() const
{
    return AABB(vec3(2*m_radius));
}
BoundingSphere Sphere::getBoundingSphere() const
{
    return BoundingSphere(m_radius);
}
