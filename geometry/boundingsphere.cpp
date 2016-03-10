#include "boundingsphere.h"

using namespace glm;

BoundingSphere::BoundingSphere(float radius, vec3 position)
{
    m_radius = radius ;
    m_position = position ;
}
float BoundingSphere::getRadius() const
{
    return m_radius;
}
vec3 BoundingSphere::getPosition() const
{
    return m_position;
}
