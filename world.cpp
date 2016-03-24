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
}
void World::translateObject(Object& obj, vec3 t)
{
    m_pworld.translateObject(obj.getPObject(), t);
}
void World::rotateObject(Object& obj, vec3 t)
{
    obj.getPObject()->rotate(t);
}
PWorld& World::getPWorld()
{
    return m_pworld;
}
