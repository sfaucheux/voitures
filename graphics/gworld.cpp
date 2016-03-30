#include "gworld.h"

using namespace glm;

GWorld::GWorld()
{
}

GWorld::~GWorld()
{
}

void GWorld::addObject(Drawable* obj)
{
    m_objects.push_back(obj);
}

void GWorld::translateObject(Drawable* obj, vec3 t)
{
    //obj->translate(t);   
}

void GWorld::draw(const Renderer& rdr, GLenum mode)
{
    for(auto it = m_objects.begin() ; it != m_objects.end() ; it++)
    {
        rdr.draw(**it, mode);
    }
}
