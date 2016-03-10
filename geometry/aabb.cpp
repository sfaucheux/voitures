#include "aabb.h"

using namespace glm;

AABB::AABB(glm::vec3 size, glm::vec3 position)
{
    m_size = size;
    m_position = position;
}
vec3 AABB::getPosition() const
{
    return m_position;
}
vec3 AABB::getSize() const
{
    return m_size ;
}
float AABB::getBottomPosition() const
{
    return m_position.y - m_size.y/2;
}
float AABB::getTopPosition() const
{
    return m_position.y + m_size.y/2;
}
float AABB::getLeftPosition() const
{
    return m_position.x - m_size.x/2;
}
float AABB::getRightPosition() const
{
    return m_position.x + m_size.x/2;
}
float AABB::getFrontPosition() const
{
    return m_position.z + m_size.z/2;
}
float AABB::getBackPosition() const
{
    return m_position.z - m_size.z/2;
}

