#include "sphere.h"

#include "../glm/gtx/norm.hpp"
#include "collisions.h"

using namespace std;
using namespace glm;

Sphere::Sphere(float radius)
{
    m_radius = radius;
}

bool Sphere::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Sphere::collide(const Sphere *s) const
{
    return Collision::collide(this, s);
}

bool Sphere::collide(const Box* b) const
{
    return b->collide(this);
}

bool Sphere::collide(const Mesh* b) const
{
    return false;
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Box* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Mesh* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Sphere* obj) const
{
    return Collision::collisionPoints(this, obj);
}

float Sphere::getRadius() const
{
    return m_radius;
}
