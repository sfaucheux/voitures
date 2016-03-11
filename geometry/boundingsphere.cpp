#include "boundingsphere.h"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtx/norm.hpp"

using namespace glm;

BoundingSphere::BoundingSphere(float radius, vec3 position)
{ 
    m_radius = radius ;
    m_position = position ;
}
bool BoundingSphere::collide(const BoundingSphere &s) const
{
    return distance2(getPosition(), s.getPosition()) <= (getRadius() + s.getRadius())*(getRadius() + s.getRadius());
}
float BoundingSphere::getRadius() const
{
    return m_radius;
}
vec3 BoundingSphere::getPosition() const
{
    return m_position;
}
void BoundingSphere::setPosition(glm::vec3 pos)
{
    m_position = pos;
}
