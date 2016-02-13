#include <cmath>

#include "../glm/gtx/norm.hpp"

#include "psphere.h"
#include "pbox.h"

using namespace std;
using namespace glm;

PSphere::PSphere(float radius)
{
    m_radius = radius;
}

bool PSphere::collide(PObject* obj)
{
    return obj->collideWithSphere(this);
}

bool PSphere::collideWithSphere(PSphere *s)
{
    return distance2(m_position, s->getPosition()) < (m_radius + s->getRadius())*(m_radius + s->getRadius());
}

bool PSphere::collideWithBox(PBox* b)
{
    return b->collideWithSphere(this);
}

bool PSphere::collideWithMesh(PMesh* b)
{
    return false;
}

vector<tuple<vec3,vec3>> PSphere::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithSphere(this);
}

vector<tuple<vec3,vec3>> PSphere::collisionPointsWithBox(PBox* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PSphere::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PSphere::collisionPointsWithSphere(PSphere* obj) 
{
    //On retourne la moyenne des centres ponderees par les rayons.
    //La normale est définie comme le vecteur formé par les deux centres.
    //Suppose que les spheres sont en collision (c'est le cas, la broadphase est exacte pour les solides de base).
    vec3 point((m_radius*m_position + obj->getRadius()*obj->getPosition())/(m_radius + obj->getRadius()));
    vec3 normal(m_position - obj->getPosition());
    return vector<tuple<vec3,vec3>>({make_tuple(point, normal)});
}

float PSphere::getRadius() const
{
    return m_radius;
}
