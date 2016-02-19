#include <cmath>

#include "../glm/gtx/transform.hpp"

#include "pbox.h"
#include "psphere.h"
#include "collisions.h"

using namespace std;
using namespace glm;

PBox::PBox(float width, float height, float depth)
{
    m_width = width;
    m_height = height;   
    m_depth = depth;
    mat3 inertia(0);
    inertia[0][0] = getMass()*(height*height + depth*depth)/12.;
    inertia[1][1] = getMass()*(width*width + depth*depth)/12.;
    inertia[2][2] = getMass()*(height*height + width*width)/12.;
    setInertia(inertia);
}

float PBox::getHeight() const
{
    return m_height;
}
float PBox::getWidth() const
{
    return m_width;
}
float PBox::getDepth() const
{
    return m_depth;
}

bool PBox::collide(PObject* obj)
{
    return obj->collideWithBox(this);
}

bool PBox::collideWithBox(PBox* b)
{
    return false;
}

bool PBox::collideWithMesh(PMesh* b)
{
    return false;
}

bool PBox::collideWithSphere(PSphere *s)
{
    return collideSphereWithBox(s, this);
}

vector<tuple<vec3,vec3>> PBox::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithBox(this);
}

vector<tuple<vec3,vec3>> PBox::collisionPointsWithBox(PBox* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PBox::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PBox::collisionPointsWithSphere(PSphere* obj) 
{
    return vector<tuple<vec3,vec3>>();
}
