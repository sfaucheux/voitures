#include "psphere.h"
#include <cmath>
#include "../glm/gtx/norm.hpp"

PSphere::PSphere(float radius)
{
    m_radius = radius ;
}
int PSphere::collide(PObject* obj)
{
    return obj->collideWithSphere(this);
}
int PSphere::collideWithSphere(PSphere *s)
{
    return glm::length(m_position - s->getPosition()) - abs(m_radius + s->getRadius());
}
int PSphere::collideWithBox(PBox* b)
{
    return -1 ;
}
int PSphere::collideWithMesh(PMesh* b)
{
    return -1 ;
}
float PSphere::getRadius() const
{
    return m_radius;
}
