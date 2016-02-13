#include "pworld.h"
#include "../glm/gtx/norm.hpp"

using namespace glm;
using namespace std;

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

void PWorld::broadPhase()
{
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        for (auto jt = m_objects.begin(); jt != it; jt++)
        {
            if ((*it)->collide(*jt))
                m_potentialCollisions.push_back({*it, *jt});
        }
    }
}

void PWorld::narrowPhase()
{
    PObject *obj1, *obj2 ;
    for (auto it = m_potentialCollisions.begin(); it != m_potentialCollisions.end(); it++)
    {
        obj1 = (*it)[0];
        obj2 = (*it)[1];
        vector<tuple<vec3,vec3>> points = obj1->collisionPoints(obj2);
        for (int j = 0; j < points.size(); j++)
        {
            obj1->addContact(make_tuple(obj2, get<0>(points[j]), get<1>(points[j])));
            obj2->addContact(make_tuple(obj1, get<0>(points[j]), -get<1>(points[j])));
        }
        if (points.size())
        {
            m_collided.push_back(obj1);
            m_collided.push_back(obj2);
        }
    }
}

void PWorld::collisionResponse()
{
    for (auto it = m_collided.begin(); it != m_collided.end(); it++)
    {
        (*it)->doContactsResponse();
    }
}

void PWorld::integrate(float step)
{
    PObject* obj ;
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
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

