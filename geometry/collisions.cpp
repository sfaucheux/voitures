#include "collisions.h"
#include "../glm/gtx/norm.hpp"
#include "../glm/gtx/transform.hpp"
#include <iostream>

using namespace glm ;
using namespace std ;

float square(float f)
{
    return f * f;
}

float sgn(float f)
{
    if (f < 0)
        return -1;
    else if (f > 0)
        return 1;
    return 0;
}

bool Collisions::collide(const Sphere* obj1, const Sphere* obj2)
{
    return distance2(obj1->getPosition(), obj2->getPosition()) <= square(obj1->getRadius() + obj2->getRadius());
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* obj1, const Sphere* obj2)
{
    //On retourne la moyenne des centres ponderees par les rayons.
    //La normale est définie comme le vecteur formé par les deux centres.
    //Suppose que les spheres sont en collision (c'est le cas, la broadphase est exacte pour les solides de base).
    vec3 point((obj1->getRadius() * obj1->getPosition() + obj2->getRadius() * obj2->getPosition()) / (obj1->getRadius() + obj2->getRadius()));
    vec3 normal(obj2->getPosition()- obj1->getPosition());
    return vector<tuple<vec3,vec3>>({make_tuple(point, normal)});
}

bool Collisions::collide(const Sphere* s, const Box* b)
{
    // calculating s's position relative to b
    glm::vec3 sphPos = b->getLocalPoint(s->getPosition());

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= b->getWidth() / 2.0)
    {
        if (yc <= b->getHeight() / 2.0)
            return zc - r <= b->getDepth() / 2.0;
        if (zc <= b->getDepth() / 2.0)
            return yc - r <= b->getHeight() / 2.0;
        if (yc <= b->getHeight() / 2.0 + r)
            return square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
        return false;
    }
    else if (yc <= b->getHeight() / 2.0)
    {
        if (zc <= b->getDepth() / 2.0)
            return xc - r <= b->getWidth() / 2.0;
        if (zc <= b->getDepth() / 2.0 + r)
            return square(xc - (b->getWidth() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
        return false;
    }
    else if (zc <= b->getDepth() / 2.0)
    {
        if (xc <= b->getWidth() / 2.0 + r)
            return square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) <= square(r);
        return false;
    }
    else if ((xc <= b->getWidth() / 2.0 + r) && (yc <= b->getHeight() / 2.0 + r) && (zc <= b->getDepth() / 2.0 + r))
        return square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
    return false;
}

bool Collisions::collide(const Box* b, const Sphere* s)
{
    return collide(s, b);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* s, const Box* b)
{
    glm::vec3 collisionPoint;
    // calculating s's position relative to b
    glm::vec3 sphPos = b->getLocalPoint(s->getPosition());

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= b->getWidth() / 2.0)
    {
        if (yc <= b->getHeight() / 2.0)
        {
            if (zc - r <= b->getDepth() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.z) * glm::vec3(0, 0, r);
        }
        else if (zc <= b->getDepth() / 2.0)
        {
            if (yc - r <= b->getHeight() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.y) * glm::vec3(0, r, 0);
        }
        else if (yc <= b->getHeight() / 2.0 + r)
        {
            if (square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sphPos.x, sgn(sphPos.y) * b->getHeight() / 2.0, sgn(sphPos.z) * b->getDepth() / 2.0);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (yc <= b->getHeight() / 2.0)
    {
        if (zc <= b->getDepth() / 2.0)
        {
            if (xc - r <= b->getWidth() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.x) * glm::vec3(r, 0, 0);
        }
        else if (zc <= b->getDepth() / 2.0 + r)
        {
            if (square(xc - (b->getWidth() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sphPos.y, sgn(sphPos.z) * b->getDepth() / 2.0);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (zc <= b->getDepth() / 2.0)
    {
        if (xc <= b->getWidth() / 2.0 + r)
        {
            if (square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sgn(sphPos.y) * b->getHeight() / 2.0, sphPos.z);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if ((xc <= b->getWidth() / 2.0 + r) && (yc <= b->getHeight() / 2.0 + r) && (zc <= b->getDepth() / 2.0 + r))
    {
        if (square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
            collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sgn(sphPos.y) * b->getHeight() / 2.0, sgn(sphPos.z) * b->getDepth() / 2.0);
    }
    else
    {
        return vector<tuple<vec3,vec3>>();
    }
    return vector<tuple<vec3,vec3>>({make_tuple(b->getWorldPoint(collisionPoint), mat3(b->getRotationMatrix()) * (collisionPoint - sphPos))});
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* b, const Sphere* s)
{
    vector<tuple<vec3,vec3>> r = collisionPoints(s,b);
    for(auto it = r.begin() ; it != r.end() ; it++)
    {
        get<1>(*it) = -get<1>(*it) ;
    }
    return r;
}

bool Collisions::collide(const Sphere* s, const Mesh* m)
{
    return false;
}

bool Collisions::collide(const Mesh* m, const Sphere* s)
{
    return collide(s, m);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* s, const Mesh* m)
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* m, const Sphere* s)
{
    return vector<tuple<vec3,vec3>>();
}

bool Collisions::collide(const Box* obj1, const Box* obj2)
{
    return false;
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* obj1, const Box* obj2)
{
    return vector<tuple<vec3,vec3>>();
}

bool Collisions::collide(const Box* b, const Mesh* m)
{
    return false;
}

bool Collisions::collide(const Mesh* m, const Box* b)
{
    return collide(b, m);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* b, const Mesh* m)
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* m, const Box* b)
{
    return vector<tuple<vec3,vec3>>();
}

bool Collisions::collide(const Mesh* obj1, const Mesh* obj2)
{
    return false;
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* obj1, const Mesh* obj2)
{
    return vector<tuple<vec3,vec3>>();
}
