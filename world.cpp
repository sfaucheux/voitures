#include "world.h"

using namespace std;
using namespace glm;

World::World() : m_pworld(vec3(0,0,-10))
{

}

World::~World()
{

}

void World::addObject(const Object& obj)
{
    m_pworld.addObject(obj.getPObject());
    m_gworld.addObject(obj.getDrawable());
}

void World::translateObject(Object& obj, vec3 t)
{
    m_pworld.translateObject(obj.getPObject(), t);
    m_gworld.translateObject(obj.getDrawable(), t);
}

void World::rotateObject(Object& obj, vec3 t)
{
    obj.getPObject()->rotate(t);
    //obj.getDrawable()->rotate(t);
}

PWorld& World::getPWorld()
{
    return m_pworld;
}

GWorld& World::getGWorld()
{
    return m_gworld;
}
