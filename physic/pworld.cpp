#include "pworld.h"
#include "../glm/gtx/norm.hpp"

using namespace glm ;

PWorld::PWorld(vec3 gravity)
{
    m_gravity = gravity ;
}
void PWorld::setGravity(vec3 g)
{
    m_gravity = g;
}
void PWorld::addObject(PObject* object)
{
    m_objects.push_back(object);
}
void PWorld::removeObject(PObject* object)
{
    m_objects.remove(object);
}
void PWorld::update(float step)
{
    //Integration des grandeurs
    integrate(step);
}
void PWorld::integrate(float step)
{
    PObject* obj ;
    for(auto it = m_objects.begin() ; it != m_objects.end() ; it++)
    {
        obj = *it ;

        //On ajoute la gravité.
        obj->addForce(m_gravity*obj->getMass());
        obj->setAcceleration(obj->getForces()/obj->getMass());
        obj->setAngularAcceleration(inverse(obj->getInertia())*obj->getTorques());
        obj->setVelocity(obj->getVelocity() + obj->getAcceleration() * step);
        obj->setAngularVelocity(obj->getAngularVelocity() + obj->getAngularAcceleration() * step);

        //On simule les effets des frottements
        obj->setVelocity(obj->getVelocity()/(length2((obj->getVelocity()*obj->getLinearDamping()*step))+1));
        obj->setAngularVelocity(obj->getAngularVelocity()/(obj->getAngularVelocity()*obj->getAngularDamping()*step + vec3(1)));

        obj->translate(obj->getVelocity() * step);
        obj->rotate(obj->getAngularVelocity() * step);

        //On réinitialise les forces et couples.
        obj->resetActions();

    }
}

