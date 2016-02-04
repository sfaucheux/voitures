#include "pworld.h"

using namespace glm ;

PWorld::PWorld()
{

}
void PWorld::setGravity(vec3 g)
{
    m_gravity = g;
}
void PWorld::addObject(PObject* object)
{
    m_objects.push_back(object);
}
void PWorld::removeObject(PObject* object)
{
    m_objects.remove(object);
}

