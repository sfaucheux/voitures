#include <cmath>

#include "../glm/gtx/transform.hpp"

#include "pbox.h"
#include "psphere.h"

using namespace std;
using namespace glm;

PBox::PBox(float width, float height, float depth, Coordinates& coord) : PObject(coord)
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
    return false;
}

bool PBox::collideWithMesh(PMesh* b)
{
    return false;
}

bool PBox::collideWithSphere(PSphere *s)
{
    // calculating s's position relative to this
    // TODO : this is false
    glm::vec3 sphPos = s->getCoordinates().getPosition() - m_coord.getPosition();
    sphPos = glm::vec3(glm::rotate(-m_coord.getRotation().x, glm::vec3(1, 0, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-m_coord.getRotation().y, glm::vec3(0, 1, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-m_coord.getRotation().z, glm::vec3(0, 0, 1)) * glm::vec4(sphPos, 1));

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
/*    // calculating s's position relative to this
    glm::vec3 sphPos = s->getPosition() - m_position;
    sphPos = glm::vec3(glm::rotate(-m_angle.x, glm::vec3(1, 0, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-m_angle.y, glm::vec3(0, 1, 0)) * glm::vec4(sphPos, 1));
    sphPos = glm::vec3(glm::rotate(-m_angle.z, glm::vec3(0, 0, 1)) * glm::vec4(sphPos, 1));

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= m_width / 2.0)
    {
        if (yc <= m_height / 2.0)
            if (zc - r <= m_depth / 2.0)
                collisionPoint = sphPos - sgn(sphPos.z) * glm::vec3(0, 0, r);
        if (zc <= m_depth / 2.0)
            if (yc - r <= m_height / 2.0)
                collisionPoint = sphPos - sgn(sphPos.y) * glm::vec3(0, r, 0);
        else if (yc <= m_height / 2.0 + r)
            if (square(yc - (m_height / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sphPos.x, sgn(sphPos.y) * m_height / 2.0, sgn(sphPos.z) * m_depth / 2.0);
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (yc <= m_height / 2.0)
    {
        if (zc <= m_depth / 2.0)
            if (xc - r <= m_width / 2.0)
                collisionPoint = sphPos - sgn(sphPos.x) * glm::vec3(r, 0, 0);
        else if (zc <= m_depth / 2.0 + r)
            if (square(xc - (m_width / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * m_width / 2.0, sphPos.y, sgn(sphPos.z) * m_depth / 2.0);
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (zc <= m_depth / 2.0)
    {
        if (xc <= m_width / 2.0 + r)
            if (square(xc - (m_width / 2.0)) + square(yc - (m_height / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * m_width / 2.0, sgn(sphPos.y) * m_height / 2.0, sphPos.z);
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if ((xc <= m_width / 2.0 + r) && (yc <= m_height / 2.0 + r) && (zc <= m_depth / 2.0 + r))
        if (square(xc - (m_width / 2.0)) + square(yc - (m_height / 2.0)) + square(zc - (m_depth / 2.0)) <= square(r))
            collisionPoint = glm::vec3(sgn(sphPos.x) * m_width / 2.0, sgn(sphPos.y) * m_height / 2.0, sgn(sphPos.z) * m_depth / 2.0);
    else*/
        return vector<tuple<vec3,vec3>>();
}
