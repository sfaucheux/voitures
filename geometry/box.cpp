#include "box.h"

#include <cmath>
#include "../glm/gtx/transform.hpp"
#include "../glm/gtx/norm.hpp"
#include "collisions.h"



using namespace std;
using namespace glm;

Box::Box(float width, float height, float depth) : m_size(width, height, depth)
{
}

Box::Box(vec3 size) : m_size(size)
{
}

Box::~Box()
{
}
array<glm::vec3,8> Box::getVertices() const
{
    return {getWorldPoint(vec3( m_size[0] / 2, -m_size[1] / 2, -m_size[2] / 2)),
        getWorldPoint(vec3( m_size[0] / 2, -m_size[1] / 2, m_size[2] / 2)),
        getWorldPoint(vec3(-m_size[0] / 2, -m_size[1] / 2, -m_size[2] / 2)),
        getWorldPoint(vec3(-m_size[0] / 2, -m_size[1] / 2, m_size[2] / 2)),
        getWorldPoint(vec3( m_size[0] / 2, m_size[1] / 2, -m_size[2] / 2)),
        getWorldPoint(vec3( m_size[0] / 2, m_size[1] / 2, m_size[2] / 2)),
        getWorldPoint(vec3(-m_size[0] / 2, m_size[1] / 2, m_size[2] / 2)),
        getWorldPoint(vec3(-m_size[0] / 2, m_size[1] / 2, -m_size[2] / 2))};
}
float Box::getHeight() const
{
    return m_size[1];
}

float Box::getWidth() const
{
    return m_size[0];
}

float Box::getDepth() const
{
    return m_size[2];
}

vec3 Box::getSize() const
{
    return m_size;
}
bool Box::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Box::collide(const Sphere *s) const
{
    return Collisions::collide(s, this);
}

bool Box::collide(const Box* b) const
{
    return Collisions::collide(b, this);
}

bool Box::collide(const Mesh* m) const
{
    return Collisions::collide(m, this);
}

Contact* Box::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

Contact* Box::collisionPoints(const Sphere* s) const
{
    return Collisions::collisionPoints(s, this);
}

Contact* Box::collisionPoints(const Box* b) const
{
    return Collisions::collisionPoints(b, this);
}

Contact* Box::collisionPoints(const Mesh* m) const
{
    return Collisions::collisionPoints(m, this);
}
AABB Box::getAABB() const
{
    float r = l2Norm(m_size);
    return AABB(vec3(r));
}
BoundingSphere Box::getBoundingSphere() const
{
    float r = l2Norm(m_size);
    return BoundingSphere(r);
}
