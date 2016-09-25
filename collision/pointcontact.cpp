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
    /*
    vec3 v1 = - obj1->getVelocity();
    vec3 v2 = - obj2->getVelocity();
    double v1x = v1.x, v1y = v1.y, v1z = v1.z;
    double v2x = v2.x, v2y = v2.y, v2z = v2.z;

    vec3 u1 = -obj1->getAngularVelocity();
    vec3 u2 = -obj2->getAngularVelocity();
    double w1 = length(u1);
    double w2 = length(u2);
    u1 /= w1;
    u2 /= w2;
    double u1x = u1.x, u1y = u1.y, u1z = u1.z;
    double u2x = u2.x, u2y = u2.y, u2z = u2.z;
    
    vec3 r1 = m_point - obj1->getPosition();
    vec3 r2 = m_point - obj2->getPosition();
    double r1x = r1.x, r1y = r1.y, r1z = r1.z;
    double r2x = r2.x, r2y = r2.y, r2z = r2.z;

    //cout << "m_A" << endl;
    double nx = m_normal.x, ny = m_normal.y, nz = m_normal.z;
    m_A = -r1x*(w1*w1)*(u1y*u1y)*nx ;
    m_A += r1x*(w1*w1)*u1y*u1x*ny;
    m_A -= r1x*(w1*w1)*(u1z*u1z)*nx;
    m_A += r1x*(w1*w1)*u1z*u1x*nz;
    m_A += (w1*w1)*u1y*u1z*r1y*nz;
    m_A += (w1*w1)*u1y*u1z*r1z*ny;
    m_A -= (w1*w1)*(u1y*u1y)*r1z*nz;
    m_A += (w1*w1)*u1y*r1y*u1x*nx;
    m_A -= (w1*w1)*(u1z*u1z)*r1y*ny;
    m_A += (w1*w1)*u1z*u1x*r1z*nx;
    m_A -= (w1*w1)*r1y*(u1x*u1x)*ny;
    m_A -= (w1*w1)*(u1x*u1x)*r1z*nz;
    m_A -= r2x*(w2*w2)*(u2y*u2y)*nx;
    m_A += r2x*(w2*w2)*u2y*u2x*ny;
    m_A -= r2x*(w2*w2)*(u2z*u2z)*nx;
    m_A += r2x*(w2*w2)*u2z*u2x*nz;
    m_A -= (w2*w2)*(u2y*u2y)*r2z*nz;
    m_A += (w2*w2)*u2y*u2z*r2y*nz;
    m_A += (w2*w2)*u2y*u2z*r2z*ny;
    m_A += (w2*w2)*u2y*r2y*u2x*nx;
    m_A -= (w2*w2)*(u2z*u2z)*r2y*ny;
    m_A += (w2*w2)*u2z*u2x*r2z*nx;
    m_A -= (w2*w2)*r2y*(u2x*u2x)*ny;
    m_A -= (w2*w2)*(u2x*u2x)*r2z*nz;
    m_A /= 2;

    m_B = 
        -r1x*w1*u1y*nz
        +r1x*w1*u1z*ny
        +w1*u1y*r1z*nx
        -w1*u1z*r1y*nx
        +w1*r1y*u1x*nz
        -w1*u1x*r1z*ny
        +v1x*nx
        -r2x*w2*u2y*nz
        +r2x*w2*u2z*ny
        +w2*u2y*r2z*nx
        -w2*u2z*r2y*nx
        +w2*u2y*u2x*nz
        -w2*u2x*r2z*ny
        +v2x*nx
        +v1y*ny
        +v2y*ny
        +v1z*nz
        +v2z*nz;

    m_C = 
        (+r1x*nx
         +r1y*ny
         +r1z*nz
         +r2x*nx
         +r2y*ny
         +r2z*nz)/2;
    //cout << m_A << ";" << m_B << ";" << m_C << endl;*/
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
    float offset = m_overlap + space;

    //Si négative ou nulle, on arrete.
    if (offset <= 0)
        return;

    /*
    //Resoud l'equation complete du mouvement avec un DSE du cos et sin à l'ordre 2
    //Le calcul des coefficients du polynome (init) depasse la précision d'un float, ça ne fonctionne pas.
    //De plus, il faudrait les recalculer car r10 et r20 changent à chaque itération.
 
    vec3 p1 = obj1->getPosition() + *t1;
    vec3 p2 = obj2->getPosition() + *t2;
    vec3 rot1 = obj1->getRotation() + *r1;
    vec3 rot2 = obj2->getRotation() + *r2;

    mat4 m1, m2;
    float norm1 = length(rot1);
    if (norm1 != 0)
        m1 = glm::rotate(glm::translate(mat4(1),p1), norm1, rot1);

    float norm2 = length(rot2);
    if (norm2 != 0)
        m2 = glm::rotate(glm::translate(mat4(1),p2), norm2, rot2);

    vec3 pos1 = vec3(m1*vec4(m_point - obj1->getPosition(),0));
    vec3 pos2 = vec3(m2*vec4(m_point - obj2->getPosition(),0));

    //Calcul de la nouvelle distance séparant les objets.
    float space = dot(m_normal, pos1 - pos2);
    //Calcul de la distance d'interpenetration restante.
    float offset = m_overlap + space;

    //Si négative ou nulle, on arrete.
    //if (offset <= 0)
        //return;

    //Calcul de C.
    float C = m_C - offset/2;

    //Calcul de delta
    float delta = m_B*m_B - 4*m_A*m_C;

    float t ;
    if (delta < 0)
    {
        cout << "pas de solution" << endl;
        return;
    }
    else if (delta > 0)
    {
        cout << "delta > 0)" << endl;
        float rDelta = sqrt(delta);
        float t1 = (-m_B+rDelta)/(2*m_A);
        float t2 = (-m_B-rDelta)/(2*m_A);
        if (t1 < 0)
        {
            if (t2 < 0)
            {
                cout << "pas de solution positive" << endl;
                return;
            }
            else
            {
                cout << "t2" << endl;
                t = t2;
            }

        }
        else
        {
            if (t2 < 0)
            {
                cout << "t1" << endl;
                t = t1;
            }
            else
            {

                cout << "les deux : t1 : " << t1 << " t2 : " << t2 << endl;
                t = (t1<t2)? t1 : t2;
            }
        }
    }
    else
    {
        cout << "delta == 0)" << endl;
        return;
        t = -m_B/(2*m_A);
    }
    *t1 -= obj1->getVelocity()*t;
    *r1 -= obj1->getAngularVelocity()*t;
    *t2 -= obj2->getVelocity()*t;
    *r2 -= obj2->getAngularVelocity()*t;*/

/*
    //Separe uniquement en fonction des vitesses linéaires, diverge un peu.

    vec3 v1 = obj1->getVelocity();
    vec3 v2 = obj2->getVelocity();
    vec3 vrel = -v2-v1;

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
*/

    //Code qui écarte juste les objets pa rapport à la normale, stable.
    
    float static1 =(obj1->isStatic()) ? 0 : 1;
    float static2 =(obj2->isStatic()) ? 0 : 1;

    *t1 += (offset*static1)/(static1+static2)*m_normal;
    *t2 += -(offset*static2)/(static1+static2)*m_normal;
   

}

void PointContact::inverse()
{
    m_normal = -m_normal;
}
