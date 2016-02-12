#include "psphere.h"
#include <cmath>
#include "../glm/gtx/norm.hpp"

using namespace std;
using namespace glm;

PSphere::PSphere(float radius)
{
    m_radius = radius ;
}
bool PSphere::collide(PObject* obj)
{
    return obj->collideWithSphere(this);
}
bool PSphere::collideWithSphere(PSphere *s)
{
    return length(m_position - s->getPosition()) - abs(m_radius + s->getRadius());
}
bool PSphere::collideWithBox(PBox* b)
{
    return false ;
}
bool PSphere::collideWithMesh(PMesh* b)
{
    return false ;
}
vector<vec3> PSphere::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithSphere(this);
}
vector<vec3> PSphere::collisionPointsWithBox(PBox* obj) 
{
    return vector<vec3>();
}
vector<vec3> PSphere::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<vec3>();
}
vector<vec3> PSphere::collisionPointsWithSphere(PSphere* obj) 
{
    return vector<vec3>();
}
float PSphere::getRadius() const
{
    return m_radius;
}
