#include "pointcontact.h"
#include <iostream>
#include "../glm/gtx/norm.hpp"

using namespace glm;
using namespace std;

PointContact::PointContact(vec3 point, vec3 normal, float overlap) : m_point(point), m_normal(normalize(normal)), m_overlap(overlap)
{
}

PointContact::~PointContact()
{
}

void PointContact::solveImpulse(PObject* obj1, PObject* obj2)
{
    //On calcule la vitesse relative.
    vec3 v12 = obj2->getPointVelocity(m_point - obj2->getPosition()) - obj1->getPointVelocity(m_point - obj1->getPosition());
    float dV = dot(m_normal, v12);

    if(dV <= 0)
        return;

    //Coefficient de restitution (1 = choc elastique, 0 = choc plastique)
    float e = 0.1;

    //masse des deux objet.
    float m1 = obj1->getMass(), m2 = obj2->getMass();

    vec3 impulse = m_normal; //Support de l'impulsion.

    float r1 = 0, r2 = 0; //Distance centre d'inertie/point de contact au carré ou s'appliquerait l'impulsion si elle était orthgonale.
    float I1 = 1, I2 = 1; //Moments d'inertie.

    //Si la réaction n'est pas une simple translation.
    if(l1Norm(cross(v12, m_normal)) != 0)
    {
        vec3 tan = normalize(cross(m_normal, cross(v12, m_normal)));

        //Coefficient de frottement dynamique.
        //Pour le statique c'est plus compliqué à simuler.
        float fs =  0.45;
        float fd =  0.4;
        float f = fd;

        float tangentVelocity = dot(v12, tan);
        float normalVelocity = dot(v12, m_normal);

        //Si glissement.
        if(tangentVelocity > f*normalVelocity)
            tangentVelocity = f*normalVelocity;

        //On calcule le support de l'impulsion.
        impulse = normalize(normalVelocity*m_normal + tangentVelocity*tan);

        //On calcule les deux axes de rotation.
        vec3 axis1 = cross(m_point - obj1->getPosition(),impulse);
        vec3 axis2 = cross(m_point - obj2->getPosition(),impulse);

        //On recupere les moments d'inertie associes aux axes
        I1 = obj1->getInertiaMomentum(axis1);
        I2 = obj2->getInertiaMomentum(axis2);

        //Distance entre le centres d'inertie et le point de collision au carre.
        r1 = length2(cross(m_point - obj1->getPosition(), impulse));
        r2 = length2(cross(m_point - obj2->getPosition(), impulse));
    }

    //Si les objets sont statiques, leur masse est infinie.
    //On utilise alors 0 ou 1 en fateur des expression ou l'on divise par une masse.
    float static1 =(obj1->isStatic()) ? 0 : 1;
    float static2 =(obj2->isStatic()) ? 0 : 1;

    impulse = (1+e)*dot(v12, impulse)/(static1/m1 + static2/m2 + static1*r1/I1 + static2*r2/I2) * impulse;
    obj1->setLinearImpulse(impulse);
    obj2->setLinearImpulse(-impulse);
    obj1->setAngularImpulse(cross(m_point - obj1->getPosition(), impulse));
    obj2->setAngularImpulse(-cross(m_point - obj2->getPosition(), impulse));
}

void PointContact::solvePosition(PObject* obj1, PObject* obj2, glm::vec3* t1, glm::vec3* t2, glm::vec3* r1, glm::vec3* r2)
{
    //Calcul de la nouvelle distance séparant les objets.
    float space = dot(m_normal, *t1 - *t2);
    //Calcul de la distance d'interpenetration restante.
    float offset = m_overlap - space;

    //Si négative ou nulle, on arrete.
    if (offset <= 0)
        return;

    vec3 v1 = obj1->getVelocity();
    vec3 v2 = obj2->getVelocity();
    vec3 vrel = v2-v1;

    //Si les objets s'éloignent, on arrête.
    if (dot(vrel, m_normal) < 0) 
        return;

    //Calcul du pas de temps qui a été necessaire aux objets pour s'interpenetrer.
    float step = offset / (dot(m_normal, vrel));

    //retour dans le passé, du pas de temps calculé.
    if (!obj1->isStatic())
        *t1 -=  v1 * step;
    if (!obj2->isStatic())
        *t2 -=  v2 * step;

    /*
    //Code qui écarte juste les objets pa rapport à la normale, stable.
    
    float static1 =(obj1->isStatic()) ? 0 : 1;
    float static2 =(obj2->isStatic()) ? 0 : 1;

    *t1 += (offset*static1)/(static1+static2)*m_normal;
    *t2 += -(offset*static2)/(static1+static2)*m_normal;
    
    */
}

void PointContact::inverse()
{
    m_normal = -m_normal;
}
