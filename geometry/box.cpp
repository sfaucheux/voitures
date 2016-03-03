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
    return obj->collide(this);
}

bool Box::collide(const Box* b) const
{
    return false;
}

bool Box::collide(const Mesh* b) const
{
    return false;
}

bool Box::collide(const Sphere *s) const
{
    return Collision::collide(s, this);
}

vector<tuple<vec3,vec3>> Box::collisionPoints(const Geometry* obj) const 
{
    return obj->collisionPoints(this);
}

vector<tuple<vec3,vec3>> Box::collisionPoints(const Box* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Box::collisionPoints(const Mesh* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Box::collisionPoints(const Sphere* obj) const
{
    return vector<tuple<vec3,vec3>>();
}
