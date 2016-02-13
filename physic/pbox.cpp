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
