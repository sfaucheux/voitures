#include "psphere.h"
#include "pbox.h"

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
    return -1;
}

bool PSphere::collideWithBox(PBox* b)
{
    return b->collideWithSphere(this);
}

bool PSphere::collideWithMesh(PMesh* b)
{
    return -1;
}

float PSphere::getRadius() const
{
    return m_radius;
}
