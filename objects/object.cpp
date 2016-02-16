#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::setShader(Shader* shader)
{
    m_gObj.setShader(shader);
}

PObject* Object::getPObject()
{
    return m_pObj;
}

Drawable const& Object::getDrawable() const
{
    return m_gObj;
}

const Shader* Object::getShader() const
{
    return m_gObj.getShader();
}

void Object::sync()
{
    m_gObj.setModel(m_pObj->getModel());
}

void Object::translate(glm::vec3 t)
{
    m_pObj->translate(t);
    this->sync();
}

void Object::rotate(glm::vec3 r)
{
    m_pObj->rotate(r);
    this->sync();
}
