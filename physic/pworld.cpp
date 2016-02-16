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
    //while(computeAgain)
    //{
        computeAgain = false ;
        for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
        {
            //Ne marche peut etre pas pour plusieurs points de contacts.
            //Si bug, il faudrait traiter les objets un par un et stocker tous les vecteurs puis les appliquer ensuite.
            obj1 = get<0>(*it);
            obj2 = get<1>(*it);
            vector<tuple<vec3,vec3>> points = get<2>((*it));
            for (int j = 0; j < points.size(); j++)
            {
                tie(point, normal) = points[j] ;
                vec3 v12 = obj2->getPointVelocity(point - obj2->getPosition()) - obj1->getPointVelocity(point - obj1->getPosition());
                float dV = dot(normal, v12);
                if(dV > 0)
                {
                    normal = normalize(normal);
                    vec3 impulse = computeImpulse(obj1, obj2, point, normal);
                    obj1->setLinearImpulse(impulse);
                    obj2->setLinearImpulse(-impulse);
                    obj2->setAngularImpulse(cross(point - obj1->getPosition(), impulse));
                    obj2->setAngularImpulse(-cross(point - obj2->getPosition(), impulse));
                    computeAgain = true ;
                }
            }
        }
    //}
    m_contacts.clear();
}
vec3 PWorld::computeImpulse(PObject* obj1, PObject* obj2, vec3 point, vec3 normal)
{
    //Coefficient de restitution (1 = choc elastique, 0 = choc plastique)
    float e = 1;

    //masse des deux objet.
    float m1 = obj1->getMass(), m2 = obj2->getMass() ;

    //On calcule la vitesse relative.
    vec3 v12 =  obj2->getPointVelocity(point - obj2->getPosition()) - obj1->getPointVelocity(point - obj1->getPosition());
    vec3 impulse = normal ; //Support de l'impulsion.

    float r1 = 0, r2 = 0 ; //Distance centre d'inertie/point de contact au carré ou s'appliquerait l'impulsion si elle était orthgonale.
    float I1 = 1, I2 = 1 ; //Moments d'inertie.

    //Si la réaction n'est pas une simple translation.
    if(l1Norm(cross(v12, normal)) != 0)
    {
        vec3 tan = normalize(cross(normal, cross(v12, normal)));
        
        //Coefficient de frottement dynamique.
        //Pour le statique c'est plus compliqué à simuler.
        float f =  0.5 ;

        float tangentVelocity = dot(v12, tan) ;
        float normalVelocity = dot(v12, normal) ;

        //Si glissement.
        if(tangentVelocity > f*normalVelocity)
            tangentVelocity = f*tangentVelocity ;

        //On calcule le support de l'impulsion.
        impulse = normalize(normalVelocity*normal + tangentVelocity*tan) ;

        //On calcule les deux axes de rotation.
        vec3 axis1 = cross(point - obj1->getPosition(),impulse) ;
        vec3 axis2 = cross(point - obj2->getPosition(),impulse) ;

        //On recupere les moments d'inertie associes aux axes
        I1 = obj1->getInertiaMomentum(axis1);
        I2 = obj2->getInertiaMomentum(axis2);

        //Distance entre le centres d'inertie et le point de collision au carre.
        r1 = length2(cross(point - obj1->getPosition(), impulse));
        r2 = length2(cross(point - obj2->getPosition(), impulse));
    }
    //Si les objets sont statiques, leur masse est infinie.
    //On utilise alors 0 ou 1 en fateur des expression ou l'on divise par une masse.
    float static1 =(obj1->isStatic()) ? 0 : 1 ;
    float static2 =(obj2->isStatic()) ? 0 : 1 ;
    return  (1+e)*dot(v12, impulse)/((static1/m1+static2/m2) + static1*r1/I1 + static2*r2/I2) * impulse ;
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
        obj->setAngularAcceleration(obj->getInertiaInv()*obj->getTorques());
        obj->setVelocity(obj->getVelocity() + obj->getAcceleration() * step);
        obj->setAngularVelocity(obj->getAngularVelocity() + obj->getAngularAcceleration() * step);

        //On simule les effets des frottements
        obj->setVelocity(obj->getVelocity()/(length2((obj->getVelocity()*obj->getLinearDamping()*step))+1));
        //obj->setAngularVelocity(obj->getAngularVelocity()/(obj->getAngularVelocity()*obj->getAngularDamping()*step + vec3(1)));

        obj->translate(obj->getVelocity() * step);
        obj->rotate(obj->getAngularVelocity() * step);
        //On réinitialise les forces et couples.
        obj->resetActions();

    }
}

