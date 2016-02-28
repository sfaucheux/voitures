#include "../glm/gtc/matrix_transform.hpp"
#include "pobject.h"

using namespace glm;
using namespace std;

PObject::PObject(Coordinates& coord) : m_centroid(0), m_coord(coord), m_inertia(1), m_velocity(0), m_angularVelocity(0), m_acceleration(0), m_angularAcceleration(0)
{
    m_mass = 1;
    m_volume = 1;
    m_static = false ;
    m_awake= true ;
    m_static = false ;
    m_linearDamping = 0.1;
    m_angularDamping = 0.1;
}

PObject::~PObject()
{
}

void PObject::doContactsResponse()
{

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

float PObject::getMass()
{
    return m_mass;
}

Coordinates& PObject::getCoordinates()
{
    return m_coord;
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

vec3 PObject::getForces()
{
    return m_forces;
}

vec3 PObject::getTorques()
{
    return m_torques;
}

void PObject::addForce(vec3 f)
{
    m_forces += f ;
}

void PObject::addTorque(vec3 t)
{
    m_torques += t ;
}

void PObject::addContact(tuple<PObject*, vec3, vec3> contact)
{
    m_contacts.push_back(contact);
}

glm::mat3 PObject::getInertia()
{
    return m_inertia;
}

void PObject::resetActions()
{
    m_forces = vec3(0);
    m_torques = vec3(0);
}

float PObject::getLinearDamping()
{
    return m_linearDamping ;
}

float PObject::getAngularDamping()
{
    return m_angularDamping ;
}
