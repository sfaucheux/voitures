#include "aabb.h"

using namespace glm;

AABB::AABB(glm::vec3 size, glm::vec3 position)
{
    m_size = size;
    m_position = position;
}
AABB::RESULT AABB::relativePosition(AABB *b) const
{

    if(b->getBottomPosition() > getTopPosition())
       return OUTSIDE;
    if(b->getTopPosition() < getBottomPosition())
        return OUTSIDE;
    if(b->getRightPosition() < getLeftPosition()) 
        return OUTSIDE;
    if(b->getLeftPosition() > getRightPosition())
        return OUTSIDE;
    if(b->getFrontPosition() < getBackPosition())
       return OUTSIDE;
    if(b->getBackPosition() > getFrontPosition())
        return OUTSIDE;

    if(b->getBottomPosition() < getBottomPosition())
       return INTERSECT;
    if(b->getTopPosition() > getTopPosition())
        return INTERSECT;
    if(b->getRightPosition() > getRightPosition()) 
        return INTERSECT;
    if(b->getLeftPosition() < getLeftPosition())
        return INTERSECT;
    if(b->getFrontPosition() > getFrontPosition())
       return INTERSECT;
    if(b->getBackPosition() < getBackPosition())
        return INTERSECT;

    return INSIDE;
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

