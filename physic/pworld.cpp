#include "pworld.h"
#include "../glm/gtx/norm.hpp"
#include <iostream>

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
    //Determination des objets potentiellements en contact.
    broadPhase();
    //Determiantion des points et normales de contacts (s'il y en a).
    narrowPhase();
    //Reponse aux collisions.
    collisionResponse();
    //Integration des grandeurs.
    integrate(step);
}

void PWorld::broadPhase()
{
    //Pour chaque couple i,j (j < i), on cherche une collision potentielle.
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
    //Pour chaque objets potentiellements en collision, on cherche les points et normales de contact.
    PObject *obj1, *obj2 ;
    for (auto it = m_potentialCollisions.begin(); it != m_potentialCollisions.end(); it++)
    {
        obj1 = (*it)[0];
        obj2 = (*it)[1];
        vector<tuple<vec3,vec3>> points = obj1->collisionPoints(obj2);
        if (points.size())
        {
            m_contacts.push_back(make_tuple(obj1, obj2, points));
        }
    }
    m_potentialCollisions.clear();
}

void PWorld::collisionResponse()
{
    /* ATTENTION : La terminaison n'est pas certaine !
     * On boucle sur tous les objets en contact jusqu'à ce qu'ils s'éloignent tous !
     * On calcule la reponse a une collision et on met a jour les vitesses.
     * Cela revient à traiter les collision d'objet 2 à 2 (aucune collision en même temps)
     * mais avec un pas de temps nul.
     */
    bool computeAgain = true;
    PObject *obj1, *obj2;
    vec3 normal, point ;
    while(computeAgain)
    {
        computeAgain = false ;
        for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
        {
            obj1 = get<0>(*it);
            obj2 = get<1>(*it);
            vector<tuple<vec3,vec3>> points = get<2>((*it));
            for (int j = 0; j < points.size(); j++)
            {
                tie(point, normal) = points[j] ;
                vec3 relV = obj1->getPointVelocity(point) - obj2->getPointVelocity(point)  ;
                float dV = dot(normal, relV);
                if(dV < 0)
                {
                    normal = normalize(normal);
                    float j = computeImpulse(obj1, obj2, point, normal);
                    obj1->setLinearImpulse(j*normal);
                    obj2->setLinearImpulse(-j*normal);
                    obj2->setAngularImpulse(j*cross(normal,obj1->getLocalPoint(point)));
                    obj2->setAngularImpulse(-j*cross(normal,obj2->getLocalPoint(point)));
                    computeAgain = true ;
                }
            }
        }
    }
    m_contacts.clear();
}
float PWorld::computeImpulse(PObject* obj1, PObject* obj2, vec3 point, vec3 normal)
{
    //Coefficient de restitution (1 = choc elastique, 0 = choc plastique)
    float e = 1;
    //masse des deux objet.
    float m1 = obj1->getMass(), m2 = obj2->getMass() ;
    //Distance entre le centres d'inertie et le point de collision au carré.
    float r1 = length2(cross(obj1->getLocalPoint(point), normal));
    float r2 = length2(cross(obj2->getLocalPoint(point), normal));

    //On calcule la vitesse relative.
    vec3 v12 =  obj1->getPointVelocity(obj1->getLocalPoint(point)) - obj2->getPointVelocity(obj2->getLocalPoint(point));

    //On calcule les deux axes de rotation.
    vec3 axis1 = cross(obj1->getLocalPoint(point),normal) ;
    vec3 axis2 = cross(obj2->getLocalPoint(point),normal) ;

    //vec3 tan = normalize(normal*v12);

    //On recupere les moments d'inertie associes aux axes
    float I1 = obj1->getInertiaMomentum(axis1) , I2 = obj2->getInertiaMomentum(axis2);
    float j = -(1+e)*dot(v12, normal)/((1/m1+1/m2) + r1/I1 + r2/I2);
    //float f = 0.5 ;

    //if(tgtVelocity > f*velocity)
    //    tgtVelocity = f*velocity;

        return j ;
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

