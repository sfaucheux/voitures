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

void PObject::setSpeed(glm::vec3 s)
{
    m_speed = s;
}

void PObject::setAcceleration(glm::vec3 a)
{
    m_acceleration = a;
}

void PObject::setAngularSpeed(glm::vec3 s)
{
    m_angularSpeed = s;
}

void PObject::setAngularAcceleration(glm::vec3 a)
{
    m_angularAcceleration = a;
}

void PObject::setStatic(bool s)
{
    m_static = s;
}

void PObject::rotate(glm::vec3 axis, float angle)
{
    m_model = glm::rotate(m_model, angle, axis);
}

void PObject::translate(glm::vec3 t)
{
    m_model = glm::translate(m_model, t);
}

float PObject::getMass()
{
    return m_mass;
}

glm::vec3 PObject::getSpeed()
{
    return m_speed;
}

glm::vec3 PObject::getAcceleration()
{
    return m_acceleration;
}

glm::vec3 PObject::getAngularSpeed()
{
    return m_angularSpeed;
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
