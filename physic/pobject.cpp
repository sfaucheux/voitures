#include "pobject.h"
#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "../glm/gtx/norm.hpp"
#include "../glm/gtx/euler_angles.hpp"

#include "node.h"

using namespace glm;
using namespace std;

PObject::PObject(Geometry& geo) : m_position(0), m_rotation(0), m_geometry(geo), m_AABB(geo.getAABB()), m_boundingSphere(geo.getBoundingSphere()), m_inertia(1), m_inertiaInv(1), m_velocity(0), m_angularVelocity(0), m_acceleration(0), m_angularAcceleration(0) 
{
	m_id = -1;
    m_mass = 10;
    m_static = false;
    m_awake = true ;
    m_linearDamping = 0.01;
    m_angularDamping = 0.01;
    m_node = nullptr ;
}

PObject::~PObject()
{
}

/*Accesseurs*/
int PObject::getId() const
{
	return m_id;
}
const vec3 PObject::getPosition() const
{
    return m_position;
}

const vec3& PObject::getVelocity() const
{
    return m_velocity;
}

const vec3& PObject::getAcceleration() const
{
    return m_acceleration;
}

const vec3 PObject::getRotation() const
{
    return m_rotation;
}

const vec3& PObject::getAngularVelocity() const
{
    return m_angularVelocity;
}

const vec3& PObject::getAngularAcceleration() const
{
    return m_angularAcceleration;
}

const vec3& PObject::getForces() const
{
    return m_forces;
}

const vec3& PObject::getTorques() const
{
    return m_torques;
}

const glm::mat3& PObject::getInertia() const
{
    return m_inertia;
}

const glm::mat3& PObject::getInertiaInv() const
{
    return m_inertiaInv;
}

const Geometry& PObject::getGeometry() const
{
    return m_geometry;
}

vec3 PObject::getPointVelocity(const vec3& point) const 
{
   return m_velocity + cross(m_angularVelocity, point);
}

vec3 PObject::getPointForce(const vec3& point) const 
{
   return m_forces + cross(m_torques, point);
}

bool PObject::isStatic() const
{
    return m_static;
}

float PObject::getMass() const
{
    return m_mass;
}

float PObject::getInertiaMomentum(const glm::vec3& axis) const
{
    if (l1Norm(axis) == 0)
        return 10000;
    vec3 a = normalize(axis);
    return dot(m_inertia*a, a);
}

float PObject::getLinearDamping() const
{
    return m_linearDamping;
}

float PObject::getAngularDamping() const
{
    return m_angularDamping;
}
Node* PObject::getNode() const
{
    return m_node;
}

const AABB& PObject::getAABB() const
{
    return m_AABB ;
}
/*Modificateurs*/
void PObject::setId(int id)
{
	m_id = id;
}
void PObject::setMass(float m)
{
    m = fabs(m);
    m_inertia = (m/m_mass)*m_inertia;
    m_inertiaInv = (m_mass/m)*m_inertiaInv;
    m_mass = m;
}

void PObject::setVelocity(glm::vec3 s)
{
    if (!m_static)
        m_velocity = s;
}

void PObject::setAcceleration(glm::vec3 a)
{
    if (!m_static)
        m_acceleration = a;
}

void PObject::setAngularVelocity(glm::vec3 s)
{
    if (!m_static)
        m_angularVelocity = s;
}

void PObject::setAngularAcceleration(glm::vec3 a)
{
    if (!m_static)
        m_angularAcceleration = a;
}

void PObject::setStatic(bool s)
{
    if (s)
        m_velocity = m_angularVelocity = m_acceleration = m_angularAcceleration = m_torques = m_forces = vec3(0,0,0);
    m_static = s;
}

void PObject::setLinearImpulse(glm::vec3 i)
{
    if (!m_static)
        m_velocity += i/m_mass;
}

void PObject::setAngularImpulse(glm::vec3 i)
{
    if (!m_static)
        m_angularVelocity += i/getInertiaMomentum(i);
}

void PObject::setInertia(mat3 inertia)
{
    m_inertia = inertia;
    m_inertiaInv = inverse(inertia);
}

void PObject::translate(glm::vec3 t)
{
    m_position += t;
    m_geometry.translate(t);
    m_AABB.setPosition(m_position);
    m_boundingSphere.setPosition(m_position);
}

void PObject::rotate(glm::vec3 angle)
{
    m_rotation += angle;
    m_geometry.rotate(angle);
}

void PObject::addForce(vec3 f)
{
    if (!m_static)
        m_forces += f;
}

void PObject::addTorque(vec3 t)
{
    if (!m_static)
        m_torques += t;
}

void PObject::addContact(tuple<PObject*, vec3, vec3> contact)
{
    m_contacts.push_back(contact);
}

void PObject::resetActions()
{
    m_forces = vec3(0);
    m_torques = vec3(0);
}

void PObject::setNode(Node* node)
{
    m_node = node ;
}
