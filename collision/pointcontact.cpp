#include "pointcontact.h"
#include <iostream>
#include "../glm/gtx/norm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace glm;
using namespace std;

PointContact::PointContact(vec3 point, vec3 normal, float overlap) : m_point(point), m_normal(normalize(normal)), m_overlap(overlap)
{
}

PointContact::~PointContact()
{
}
void PointContact::init(PObject* obj1, PObject* obj2)
{
    m_e = 0;
    
    m_m1 = obj1->getMass();
    m_m1inv = 1/m_m1;
    m_m2 = obj2->getMass();
    m_m2inv = 1/m_m2;

    m_r1 = m_point - obj1->getPosition();
    m_r2 = m_point - obj2->getPosition();

    m_moment1 = obj1->getInertiaInv() * cross(m_r1, m_normal);
    m_moment2 = obj2->getInertiaInv() * cross(m_r2, m_normal);

    float s1 =(obj1->isStatic()) ? 0 : 1;
    float s2 =(obj2->isStatic()) ? 0 : 1;

    m_jr = -1/(s1*m_m1inv + s2*m_m2inv + dot(s1*cross(m_moment1 , m_r1) + s2*cross(m_moment2 , m_r2), m_normal));
}

void PointContact::solveImpulse(PObject* obj1, PObject* obj2)
{
    //On calcule la vitesse relative.
    vec3 vr = obj2->getPointVelocity(m_r2) - obj1->getPointVelocity(m_r1);
    //float dV = dot(m_normal, v12);

    //if(dV <= 0)
        //return;

    float jr = (m_e+1)*m_jr*dot(vr, m_normal);

    if (dot(vr, m_normal) != 0)
    {
        m_t = vr - dot(vr, m_normal)*m_normal;
    }
    else
    {
        vec3 fe = obj2->getPointForce(m_r2) - obj1->getPointForce(m_r1);
        m_t = fe - dot(fe, m_normal)*m_normal;
    }
    m_t = normalize(m_t);

    float vt = dot(vr, m_t);
    float dynamic1 = m_m1*vt;
    float dynamic2 = m_m2*vt;
    float jf1;
    float jf2;
    float m_js = 0.5*jr;
    float m_jd = 0.4*jr;

    /*
    if (vt == 0 && m_m1*vt < dynamic1 <= m_js)
    {
        jf1 = m_m1*dot(v12, m_t);
    }
    else
    {
        jf1 = m_jd;
    }
    if (vt == 0 && m_m2*vt < dynamic2 <= m_js)
    {
        jf2 = m_m2*dot(v12, m_t);
    }
    else
    {
        jf2 = m_jd;
    }
*/

    jf1 = 0.5*abs(jr);
    jf2 = 0.5*abs(jr);

    vec3 moment1f = obj1->getInertiaInv() * cross(m_r1, m_t);
    vec3 moment2f = obj2->getInertiaInv() * cross(m_r2, m_t);
     
    cout << "mom1f" << moment1f.x << " " << moment1f.y << " " << moment1f.z << endl;
    cout << "m_mom" << m_moment1.x << " " << m_moment1.y << " " << m_moment1.z << endl;

    obj1->setVelocity(obj1->getVelocity() - (jr * m_normal - jf1 * m_t)*m_m1inv);
    obj2->setVelocity(obj2->getVelocity() + (jr * m_normal - jf2 * m_t)*m_m2inv);

    obj1->setAngularVelocity(obj1->getAngularVelocity() - (jr*m_moment1));//+ jf1*moment1f));
    obj2->setAngularVelocity(obj2->getAngularVelocity() - (jr*m_moment2));// + jf2*moment2f));
/*
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

    //A faire en dernier...
    obj1->setLinearImpulse(impulse);
    obj2->setLinearImpulse(-impulse);
    obj1->setAngularImpulse(cross(m_point - obj1->getPosition(), impulse));
    obj2->setAngularImpulse(-cross(m_point - obj2->getPosition(), impulse));*/
}

void PointContact::solvePosition(PObject* obj1, PObject* obj2, glm::vec3* t1, glm::vec3* t2, glm::vec3* r1, glm::vec3* r2)
{
    //On calcule la vitesse relative.
    vec3 v12 = obj2->getPointVelocity(m_r2) - obj1->getPointVelocity(m_r1);
    float dV = dot(m_normal, v12);

    if(dV <= 0)
        return;

    //Calcul de la nouvelle distance séparant les objets.
    float space = dot(m_normal, *t1 - *t2);
    //Calcul de la distance d'interpenetration restante.
    float offset = m_overlap - space;

    float jr = 2*m_jr*offset;

    //Si négative ou nulle, on arrete.
    if (offset <= 0)
        return;

    if (!obj1->isStatic())
    {
        *t1 += jr * m_normal*m_m1inv;
        *r1 += jr*m_moment1;
    }
    if (!obj2->isStatic())
    {
        *t2 -= jr * m_normal*m_m2inv;
        *r2 -= jr*m_moment2;
    }
}

void PointContact::inverse()
{
    m_normal = -m_normal;
}
