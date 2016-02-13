#include "psphere.h"
#include "pbox.h"

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
    return -1;
}

int PSphere::collideWithBox(PBox* b)
{
    return b->collideWithSphere(this);
}

int PSphere::collideWithMesh(PMesh* b)
{
    return -1;
}

float PSphere::getRadius() const
{
    return m_radius;
}
