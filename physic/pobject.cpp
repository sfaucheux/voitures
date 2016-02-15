#include "pobject.h"
#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "../glm/gtx/norm.hpp"

using namespace glm;
using namespace std;

PObject::PObject() : m_centroid(0), m_position(0), m_angle(0), m_inertia(1), m_velocity(0), m_angularVelocity(0), m_acceleration(0), m_angularAcceleration(0), m_model(1)
{
    m_modelInv = inverse(m_model);
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

vec3 PObject::getLocalPoint(vec3 point)
{
   return vec3(m_modelInv*vec4(point,1));
}
vec3 PObject::getPointVelocity(vec3 point)
{
   return m_velocity + cross(m_angularVelocity, point);
}
void PObject::setMass(float m)
{
    if (m >= 0.0)
        m_mass = m;
}
float PObject::getInertiaMomentum(glm::vec3 axis)
{
    if(l1Norm(axis) == 0)
        return 1;
    axis = normalize(axis);
    return dot(m_inertia*axis, axis);
}
void PObject::setLinearImpulse(glm::vec3 i)
{
    m_velocity += i/m_mass;
}
void PObject::setAngularImpulse(glm::vec3 i)
{
    m_angularVelocity += i/getInertiaMomentum(i);
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

glm::vec3 PObject::getPosition()
{
    return m_position;
}

glm::vec3 PObject::getVelocity()
{
    return m_velocity;
}

glm::vec3 PObject::getAcceleration()
{
    return m_acceleration;
}

glm::vec3 PObject::getRotation()
{
    return m_angle;
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

void PObject::rotate(glm::vec3 angle)
{
    m_angle += angle;
    m_model = glm::translate(mat4(1), m_position);
    m_model = glm::rotate(m_model, m_angle.x, vec3(1,0,0));
    m_model = glm::rotate(m_model, m_angle.y, vec3(0,1,0));
    m_model = glm::rotate(m_model, m_angle.z, vec3(0,0,1));
    m_modelInv = glm::inverse(m_model);
}

void PObject::translate(glm::vec3 t)
{
    m_position += t;
    m_model = glm::translate(mat4(1), m_position);
    m_model = glm::rotate(m_model, m_angle.x, vec3(1,0,0));
    m_model = glm::rotate(m_model, m_angle.y, vec3(0,1,0));
    m_model = glm::rotate(m_model, m_angle.z, vec3(0,0,1));
    m_modelInv = glm::inverse(m_model);
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
