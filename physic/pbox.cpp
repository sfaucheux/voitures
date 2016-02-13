#include <cmath>

#include "../glm/gtx/transform.hpp"

#include "pbox.h"
#include "psphere.h"

#include <vector>

using namespace std;
using namespace glm;

PBox::PBox(float width, float height, float depth)
{
    m_width = width;
    m_height = height;   
    m_depth = depth;
}

float square(float f)
{
    return f * f;
}

bool PBox::collide(PObject* obj)
{
    return obj->collideWithBox(this);
}

bool PBox::collideWithBox(PBox* b)
{
    return false ;
}

bool PBox::collideWithMesh(PMesh* b)
{
    return false ;
}

bool PBox::collideWithSphere(PSphere *s)
{
    // calculating s's position relative to this
    glm::vec3 sphPos = s->getPosition() - this->getPosition();
    glm::vec3 rot = this->getRotation();
    sphPos = glm::vec3(glm::rotate(-rot.x, glm::vec3(1, 0, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-rot.y, glm::vec3(0, 1, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-rot.z, glm::vec3(0, 0, 1)) * glm::vec4(sphPos, 1));

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= m_width / 2.0)
    {
        if (yc <= m_height / 2.0)
            return zc - r <= m_depth / 2.0;
        if (zc <= m_depth / 2.0)
            return yc - r <= m_height / 2.0;
        else if (yc <= m_height / 2.0 + r)
            return square(yc - (m_height / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r);
        else
            return false;
    }
    else if (yc <= m_height / 2.0)
    {
        if (zc <= m_depth / 2.0)
            return xc - r <= m_width / 2.0;
        else if (zc <= m_depth / 2.0 + r)
            return square(xc - (m_width / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r);
        else
            return false;
    }
    else if (zc <= m_depth / 2.0)
    {
        if (xc <= m_width / 2.0 + r)
            return square(xc - (m_width / 2.0)) + square(yc - (m_height / 2.0)) <= square(r);
        else
            return false;
    }
    else if ((xc <= m_width / 2.0 + r) && (yc <= m_height / 2.0 + r) && (zc <= m_depth / 2.0 + r))
        return square(xc - (m_width / 2.0)) + square(yc - (m_height / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r);
    else
        return false;
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
