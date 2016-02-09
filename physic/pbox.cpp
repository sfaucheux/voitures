#include "pbox.h"

PBox::PBox(float width, float height, float depth)
{
    m_width = width;
    m_height = height;   
    m_depth = depth;
}
int PBox::collide(PObject* obj)
{
    return obj->collideWithBox(this);
}
int PBox::collideWithSphere(PSphere *s)
{
    return -1 ; 
}
int PBox::collideWithBox(PBox* b)
{
    return -1 ;
}
int PBox::collideWithMesh(PMesh* b)
{
    return -1 ;
}
