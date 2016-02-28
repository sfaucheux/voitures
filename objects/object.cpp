#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

PObject* Object::getPObject() const
{
    return m_pObj;
}

Drawable* Object::getDrawable() const
{
    return m_gObj;
}

Coordinates& Object::getCoordinates()
{
    return m_coord;
}
