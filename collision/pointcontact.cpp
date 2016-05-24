#include "pointcontact.h"
#include "../glm/gtx/norm.hpp"

using namespace glm;

PointContact::PointContact(vec3 point, vec3 normal) : m_point(point), m_normal(normalize(normal))
{
}

PointContact::~PointContact()
{
}
vec3 PointContact::solveImpulse(PObject* obj1, PObject* obj2)
{
    vec3 v12 = obj2->getPointVelocity(m_point - obj2->getPosition()) - obj1->getPointVelocity(m_point - obj1->getPosition());
    float dV = dot(m_normal, v12);
    if(dV > 0)
    {   

        //Coefficient de restitution (1 = choc elastique, 0 = choc plastique)
        float e = 0.5;

        //masse des deux objet.
        float m1 = obj1->getMass(), m2 = obj2->getMass() ;

        //On calcule la vitesse relative.
        vec3 v12 =  obj2->getPointVelocity(m_point - obj2->getPosition()) - obj1->getPointVelocity(m_point - obj1->getPosition());

        vec3 impulse = m_normal ; //Support de l'impulsion.

        float r1 = 0, r2 = 0 ; //Distance centre d'inertie/point de contact au carré ou s'appliquerait l'impulsion si elle était orthgonale.
        float I1 = 1, I2 = 1 ; //Moments d'inertie.

        //Si la réaction n'est pas une simple translation.
        if(l1Norm(cross(v12, m_normal)) != 0)
        {
            vec3 tan = normalize(cross(m_normal, cross(v12, m_normal)));

            //Coefficient de frottement dynamique.
            //Pour le statique c'est plus compliqué à simuler.
            float f =  0.4;

            float tangentVelocity = dot(v12, tan) ;
            float normalVelocity = dot(v12, m_normal) ;

            //Si glissement.
            if(tangentVelocity > f*normalVelocity)
                tangentVelocity = f*normalVelocity ;

            //On calcule le support de l'impulsion.
            impulse = normalize(normalVelocity*m_normal + tangentVelocity*tan) ;

            //On calcule les deux axes de rotation.
            vec3 axis1 = cross(m_point - obj1->getPosition(),impulse) ;
            vec3 axis2 = cross(m_point - obj2->getPosition(),impulse) ;

            //On recupere les moments d'inertie associes aux axes
            I1 = obj1->getInertiaMomentum(axis1);
            I2 = obj2->getInertiaMomentum(axis2);

            //Distance entre le centres d'inertie et le point de collision au carre.
            r1 = length2(cross(m_point - obj1->getPosition(), impulse));
            r2 = length2(cross(m_point - obj2->getPosition(), impulse));
        }

        //Si les objets sont statiques, leur masse est infinie.
        //On utilise alors 0 ou 1 en fateur des expression ou l'on divise par une masse.
        float static1 =(obj1->isStatic()) ? 0 : 1 ;
        float static2 =(obj2->isStatic()) ? 0 : 1 ;

        return (1+e)*dot(v12, impulse)/(static1/m1 + static2/m2 + static1*r1/I1 + static2*r2/I2) * impulse ;
    }
    else
    {
        return vec3(0);
    }

}
vec3 PointContact::solvePosition(PObject* p1, PObject* p2)
{

}

void PointContact::inverse()
{
    m_normal = -m_normal;
}
