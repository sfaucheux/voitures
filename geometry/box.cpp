#include "box.h"

#include <cmath>
#include "../glm/gtx/transform.hpp"
#include "collisions.h"



using namespace std;
using namespace glm;

Box::Box(float width, float height, float depth)
{
    m_width = width;
    m_height = height;   
    m_depth = depth;
}
Box::~Box()
{
}

float Box::getHeight() const
{
    return m_height;
}

float Box::getWidth() const
{
    return m_width;
}

float Box::getDepth() const
{
    return m_depth;
}

bool Box::collide(const Geometry* obj) const
{
    return obj->collideWithBox(this);
}

bool Box::collideWithSphere(const Sphere *s) const
{
    return Collisions::collide(this, s);
}

bool Box::collideWithBox(const Box* b) const
{
    return Collisions::collide(this, b);
}

bool Box::collideWithMesh(const Mesh* m) const
{
    return Collisions::collide(this, m);
}

vector<tuple<vec3,vec3>> Box::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPointsWithBox(this);
}

vector<tuple<vec3,vec3>> Box::collisionPointsWithSphere(const Sphere* s) const
{
    return Collisions::collisionPoints(this, s);
}

vector<tuple<vec3,vec3>> Box::collisionPointsWithBox(const Box* b) const
{
    return Collisions::collisionPoints(this, b);
}

vector<tuple<vec3,vec3>> Box::collisionPointsWithMesh(const Mesh* m) const
{
    return Collisions::collisionPoints(this, m);
}
