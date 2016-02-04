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
    return &m_pObj;
}

Drawable const& Object::getDrawable() const
{
    return m_gObj;
}

const Shader* Object::getShader() const
{
    return m_gObj.getShader();
}

void Object::load(std::string filename)
{
    m_mesh.loadObject(filename);
    m_gObj.load(m_mesh.getVertices(), m_mesh.getIndices());
}

void Object::sync()
{
    glm::vec3 rot = m_pObj.getRotation();

    m_gObj.setModel(glm::mat4(1.0));
    m_gObj.translate(m_pObj.getPosition());
    m_gObj.rotate(glm::vec3(1, 0, 0), rot.x);
    m_gObj.rotate(glm::vec3(0, 1, 0), rot.y);
    m_gObj.rotate(glm::vec3(0, 0, 1), rot.z);
}

void Object::translate(glm::vec3 t)
{
    m_pObj.translate(t);
    m_gObj.translate(t);
}

void Object::rotate(glm::vec3 r)
{
    m_pObj.rotate(r);
    m_gObj.rotate(glm::vec3(1, 0, 0), r.x);
    m_gObj.rotate(glm::vec3(0, 1, 0), r.y);
    m_gObj.rotate(glm::vec3(0, 0, 1), r.z);
}

