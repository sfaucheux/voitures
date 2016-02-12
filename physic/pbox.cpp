#include "pbox.h"

#include <vector>

using namespace std;
using namespace glm;

PBox::PBox(float width, float height, float depth)
{
    m_width = width;
    m_height = height;   
    m_depth = depth;
}
bool PBox::collide(PObject* obj)
{
    return obj->collideWithBox(this);
}
bool PBox::collideWithSphere(PSphere *s)
{
    return false ; 
}
bool PBox::collideWithBox(PBox* b)
{
    return false ;
}
bool PBox::collideWithMesh(PMesh* b)
{
    return false ;
}
vector<vec3> PBox::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithBox(this);
}
vector<vec3> PBox::collisionPointsWithBox(PBox* obj) 
{
    return vector<vec3>();
}
vector<vec3> PBox::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<vec3>();
}
vector<vec3> PBox::collisionPointsWithSphere(PSphere* obj) 
{
    return vector<vec3>();
}
