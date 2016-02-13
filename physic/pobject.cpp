#include "pobject.h"
#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>

using namespace glm;
using namespace std;

PObject::PObject() : m_centroid(0), m_position(0), m_angle(0), m_inertia(1), m_velocity(0), m_angularVelocity(0), m_acceleration(0), m_angularAcceleration(0), m_model(1)
{
    m_modelInv = transpose(m_model);
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

vec3 PObject::doContactsResponse()
{
    PObject* obj;
    vec3 contactPoint;
    vec3 normal;
    float masses = 0;
    vec3 velocities(0,0,0) ;
    for(auto it = m_contacts.begin() ; it != m_contacts.end() ; it++)
    {
        tie(obj, contactPoint, normal) = *it ;
        normal = normalize(normal);
        vec3 pointVelocity = obj->getVelocity() - obj->getLocalPoint(contactPoint) * obj->getAngularVelocity();
        float velocity = dot(pointVelocity, normal);
        velocities += obj->getMass()*velocity*normal;
        masses+= obj->getMass() ;
    }
    velocities /= masses;
    m_contacts.clear();
    //Choc elastique.
    return (m_mass-masses)/(m_mass+masses)*m_velocity + (2*masses)/(masses+ m_mass)*velocities ;
    //Choc inelastique.
    //return (m_mass/(m_mass+masses))*m_velocity + (masses/(masses+ m_mass))*velocities ;
}
vec3 PObject::getLocalPoint(vec3 point)
{
   return vec3(m_modelInv*vec4(point,1));
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
    m_modelInv = glm::transpose(m_model);
}

void PObject::translate(glm::vec3 t)
{
    m_position += t;
    m_model = glm::translate(mat4(1), m_position);
    m_model = glm::rotate(m_model, m_angle.x, vec3(1,0,0));
    m_model = glm::rotate(m_model, m_angle.y, vec3(0,1,0));
    m_model = glm::rotate(m_model, m_angle.z, vec3(0,0,1));
    m_modelInv = glm::transpose(m_model);
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
