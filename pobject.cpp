#include "pobject.h"

PObject::PObject()
{
	m_mass = 0.;
	m_volume = 0.;
	m_static = false;
}

void PObject::setMass(float m)
{
    if (m >= 0.0)
        m_mass = m;
}

void PObject::setVelocity(glm::vec3 s)
{
    m_velocity = s;
}

void PObject::setAcceleration(glm::vec3 a)
{
    m_acceleration = a;
}

void PObject::setAngularVelocity(glm::vec3 s)
{
    m_angularVelocity = s;
}

void PObject::setAngularAcceleration(glm::vec3 a)
{
    m_angularAcceleration = a;
}

void PObject::setStatic(bool s)
{
    m_static = s;
}

void PObject::rotate(glm::vec3 angle)
{
    m_angle += angle ;
}

void PObject::translate(glm::vec3 t)
{
    m_position += t ;
}

float PObject::getMass()
{
    return m_mass;
}

glm::vec3 PObject::getVelocity()
{
    return m_velocity;
}

glm::vec3 PObject::getAcceleration()
{
    return m_acceleration;
}

glm::vec3 PObject::getAngularVelocity()
{
    return m_angularVelocity;
}

glm::vec3 PObject::getAngularAcceleration()
{
    return m_angularAcceleration;
}

bool PObject::isStatic()
{
    return m_static;
}

float PObject::getVolume()
{
    return m_volume;
}

PObject::~PObject()
{
}
