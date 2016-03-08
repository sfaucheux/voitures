#include "sphere.h"

#include "../glm/gtx/norm.hpp"
#include "collisions.h"

using namespace std;
using namespace glm;

Sphere::Sphere(float radius)
{
    m_radius = radius;
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

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Sphere* s) const
{
    return Collisions::collisionPoints(this, s);
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Box* b) const
{
    return Collisions::collisionPoints(this, b);
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Mesh* m) const
{
    return Collisions::collisionPoints(this, m);
}
