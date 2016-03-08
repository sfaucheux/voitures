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
    return obj->collideWithSphere(this);
}

bool Sphere::collideWithSphere(const Sphere *s) const
{
    return Collisions::collide(this, s);
}

bool Sphere::collideWithBox(const Box* b) const
{
    return Collisions::collide(this, b);
}

bool Sphere::collideWithMesh(const Mesh* m) const
{
    return Collisions::collide(this, m);
}

vector<tuple<vec3,vec3>> Sphere::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPointsWithSphere(this);
}

vector<tuple<vec3,vec3>> Sphere::collisionPointsWithSphere(const Sphere* s) const
{
    return Collisions::collisionPoints(this, s);
}

vector<tuple<vec3,vec3>> Sphere::collisionPointsWithBox(const Box* b) const
{
    return Collisions::collisionPoints(this, b);
}

vector<tuple<vec3,vec3>> Sphere::collisionPointsWithMesh(const Mesh* m) const
{
    return Collisions::collisionPoints(this, m);
}
