#include "pworld.h"
#include "../glm/gtx/norm.hpp"
#include <iostream>
#include <chrono>

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
    m_octree.addObject(object);
}

void PWorld::updateObject(PObject* object)
{
    m_octree.updateObject(object);
}
void PWorld::removeObject(PObject* object)
{
    m_octree.removeObject(object->getNode(), object);
}

void PWorld::update(float step)
{

    chrono::time_point<chrono::system_clock> begin, par, broad, narrow, col, end;
    begin = chrono::system_clock::now();

 
    PObject* obj ;
    stack<Node*> s;

    if(m_octree.getRoot() != nullptr)
        s.push(m_octree.getRoot());

    while(!s.empty())
    {
        Node* node = s.top() ;
        s.pop() ;
        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                s.push(node->getChildren()[i]);
            }
        }
        for (auto it = node->getObjects().begin() ; it != node->getObjects().end() ; it++)
        {
            obj = *it ;

            //On ajoute la gravité.
            obj->addForce(m_gravity*obj->getMass());

            //On ajoute les forces de frottement.
            obj->addForce(-obj->getLinearDamping()*obj->getVelocity());
            obj->addTorque(-obj->getAngularDamping()*obj->getAngularVelocity());
        }
    }
    par = chrono::system_clock::now();
    //Determination des objets potentiellements en contact.
    broadPhase();
    broad = chrono::system_clock::now();
    //Determiantion des points et normales de contacts (s'il y en a).
    narrowPhase();
    narrow = chrono::system_clock::now();
    //Reponse aux collisions.
    collisionResponse();
    col = chrono::system_clock::now();
    //Integration des grandeurs.
    integrate(step);
    end = chrono::system_clock::now();
    /*
    cout << "parcourt : " << 
        chrono::duration_cast<chrono::microseconds>(par-begin).count() << "µs" << endl;
    cout << "broadPhase : " << 
        chrono::duration_cast<chrono::microseconds>(broad - par).count() << "µs" << endl ;
    cout << "narrowPhase : " << 
        chrono::duration_cast<chrono::microseconds>(narrow - broad).count() << "µs" << endl ;
    cout << "calcul reponses : " << 
        chrono::duration_cast<chrono::microseconds>(col - narrow).count() << "µs" << endl ;
    cout << "integration : " << 
        chrono::duration_cast<chrono::microseconds>(end - col).count() << "µs" << endl << endl ;*/
}

void PWorld::broadPhase()
{
    queue<pair<Node*, list<PObject*>&>> s;
    if(m_octree.getRoot() != nullptr)
        s.push({m_octree.getRoot(), *new list<PObject*>()});

    while(!s.empty())
    {
        Node* node = s.front().first;
        list<PObject*>& parentObjects = s.front().second;
        //tie(node, parentObjects) = s.top();

        //Pour chaque objet, on cherche une collision potentielle.
        for (auto it = node->getObjects().begin(); it != node->getObjects().end(); it++)
        {
            //Avec les objets du noeud.
            for (auto jt = node->getObjects().begin(); jt != it; jt++)
            {
                const Geometry *g1 = &(*it)->getGeometry(), *g2 = &(*jt)->getGeometry();
                if (g1->getBoundingSphere().collide(g2->getBoundingSphere()))
                    m_potentialCollisions.push_back({*it, *jt});
            }
            //Avec les objets passé par le parent.
            for (auto kt = parentObjects.begin(); kt != parentObjects.end() ; kt++)
            {
                const Geometry *g1 = &(*it)->getGeometry(), *g2 = &(*kt)->getGeometry();
                if (g1->getBoundingSphere().collide(g2->getBoundingSphere()))
                    m_potentialCollisions.push_back({*it, *kt});
            }
            
        }

        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                //On détermine les objets a passer.
                list<PObject*>& objects = *new list<PObject*>();
                for(auto it = parentObjects.begin() ; it != parentObjects.end() ; it++)
                {
                    if(node->getChildren()[i]->getAABB().relativePosition((*it)->getAABB()) != OUTSIDE)
                        objects.push_back(*it);
                }
                for(auto it = node->getObjects().begin() ; it != node->getObjects().end() ; it++)
                {
                    if(node->getChildren()[i]->getAABB().relativePosition((*it)->getAABB()) != OUTSIDE)
                        objects.push_back(*it);
                }

                s.push({node->getChildren()[i], objects});
            }
        }
        delete &s.front().second;
        s.pop();
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
        if(obj1->getGeometry().collide(&(obj2->getGeometry())))
        {
            Contact* c = obj1->getGeometry().collisionPoints(&(obj2->getGeometry()));
            if (c)
            {
                m_contacts.push_back({c,obj1, obj2});
            }
        }
    }
    m_potentialCollisions.clear();
}

void PWorld::collisionResponse()
{
    vector<vec3> impulses;
    impulses.resize(m_octree.getObjectCount());
    vector<vec3> positions;
    positions.resize(m_octree.getObjectCount());


    PObject *obj1, *obj2;
    vec3 normal, point ;
    for (int i = 0 ; i < 50 ; i++) 
    {
        for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
        {
            obj1 = get<1>(*it);
            obj2 = get<2>(*it);
            Contact* c = get<0>((*it));
            vec3 impulse = c->solveImpulse(obj1, obj2);
            obj1->setLinearImpulse(impulse);
            obj2->setLinearImpulse(-impulse);
            obj1->setAngularImpulse(cross(point - obj1->getPosition(), impulse));
            obj2->setAngularImpulse(-cross(point - obj2->getPosition(), impulse));
        }
    }
    for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
    {
        Contact* c = get<0>((*it));
        vec3 impulse = c->solveImpulse(obj1, obj2);
        obj1->setLinearImpulse(impulse);
        obj2->setLinearImpulse(-impulse);
        obj1->setAngularImpulse(cross(point - obj1->getPosition(), impulse));
        obj2->setAngularImpulse(-cross(point - obj2->getPosition(), impulse));
    }

    m_contacts.clear();

}
/*
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
        float f =  0.4;

        float tangentVelocity = dot(v12, tan) ;
        float normalVelocity = dot(v12, normal) ;

        //Si glissement.
        if(tangentVelocity > f*normalVelocity)
            tangentVelocity = f*normalVelocity ;

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

    return (1+e)*dot(v12, impulse)/(static1/m1 + static2/m2 + static1*r1/I1 + static2*r2/I2) * impulse ;
}*/
void PWorld::integrate(float step)
{
    vector<PObject*> objVector ;
    objVector.resize(m_octree.getObjectCount());

    PObject* obj ;
    stack<Node*> s;
    if(m_octree.getRoot() != nullptr)
        s.push(m_octree.getRoot());

    int i = 0 ;
    while(!s.empty())
    {
        Node* node = s.top();
        s.pop();
        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                s.push(node->getChildren()[i]);
            }
        }
        for(auto it = node->getObjects().begin() ; it != node->getObjects().end() ; it++)
        {
            objVector[i] = (*it) ;
            ++i;
        }
    }
    for(int j = 0 ; j < i ; j++)
    {
        obj = objVector[j];
        //On calcule les forces à partir des accélérations.
        obj->setAcceleration(obj->getForces()/obj->getMass());
        obj->setAngularAcceleration(obj->getInertiaInv()*obj->getTorques());

        //On integre les accelerations.
        obj->setVelocity(obj->getVelocity() + obj->getAcceleration() * step);
        obj->setAngularVelocity(obj->getAngularVelocity() + obj->getAngularAcceleration() * step);

        //On integre les vitesses.
        translateObject(obj, obj->getVelocity() * step);
        obj->rotate(obj->getAngularVelocity() * step);

        //On réinitialise les forces et couples.
        obj->resetActions();

    }
}
void PWorld::translateObject(PObject* obj, vec3 t)
{
    obj->translate(t);
    updateObject(obj);
}
const Octree& PWorld::getOctree() const
{
    return m_octree ;
}
