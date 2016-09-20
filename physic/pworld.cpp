#include "pworld.h"
#include "../glm/gtx/norm.hpp"
#include <iostream>
#include <chrono>
#include <queue>

using namespace glm;
using namespace std;

PWorld::PWorld(vec3 gravity)
{
    m_gravity = gravity ;
    m_root = nullptr;
}

PWorld::~PWorld()
{
    if(m_root != nullptr)
        delete m_root;
}

void PWorld::setGravity(vec3 g)
{
    m_gravity = g;
}

const PObject* PWorld::getPObject(int id) const
{
	return m_objects[id];
}
void PWorld::addObject(PObject* object)
{
    //cout << "ajout d'un objet à la racine" << endl ;
    //cout << "racine : " << m_root << endl ;
    //Si le monde est vide, on le créé autour de l'objet.
    if(m_root == nullptr)
    {
        vec3 objSize = object->getAABB().getSize();
        float size = 2.5f*std::max(std::max(objSize.x,objSize.y),objSize.z);
        m_root = new Node(object->getAABB().getPosition() - 1.5f*objSize, size, nullptr);
    }
    //On ajoute l'objet à la racine.
    m_objects.push_back(object);
    m_parents.push_back(nullptr);
	object->setId(m_objects.size()-1);
    addObject(m_root, object->getId());
}

void PWorld::addObject(Node* n, int object)
{
    Node* node = n;
    //On cherche le noeud qui puisse contenir l'objet.
    //On commence sur le noeud courant et on remonte jusqu'à la racine.
    while(node != nullptr && node->getAABB().relativePosition(m_objects[object]->getAABB()) != INSIDE)
    {
        node = node->getParent();
    }
    //Si on on a trouvé un parent capable de contenir l'objet.
    //Phase de redescente.
    if(node != nullptr)
    {   
        //cout << "noeud capable de contenir l'objet" << endl ;
        addObjectToChildren(node, object);
        return;
    }
    //Sinon le monde n'est pas assez grand, on l'agrandi.
    //cout << "pas de noeud capable de contenir l'objet" << endl ;
    addObjectOutsideWorld(object);
}

void PWorld::addObjectToChildren(Node* node, int object)
{
    //cout << "ajout d'un objet DANS le noeud spécifié" << endl ;
    while(node->hasChildren())
    {
        //On calcule la position relative du noeud courant et de l'objet.
        int relPos = 0;

        //On regarde si l'object est dans la partie haute.
        relPos += (m_objects[object]->getAABB().getBottomPosition() > node->getPosition().y + node->getSize()/2.) ? TOP : BOTTOM ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie basse
        if(!(relPos&TOP) && !(m_objects[object]->getAABB().getTopPosition() < node->getPosition().y + node->getSize()/2.))
            break;

        //On regarde si l'object est dans la partie droite.
        relPos += (m_objects[object]->getAABB().getLeftPosition() > node->getPosition().x + node->getSize()/2.) ? RIGHT : LEFT ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie gauche.
        if(!(relPos&RIGHT) && !(m_objects[object]->getAABB().getRightPosition() < node->getPosition().x + node->getSize()/2.))
            break;

        //On regarde si l'object est dans la partie devant.
        relPos += (m_objects[object]->getAABB().getBackPosition() > node->getPosition().z + node->getSize()/2.) ? FRONT : BACK ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie derriere.
        if(!(relPos&FRONT) && !(m_objects[object]->getAABB().getFrontPosition() < node->getPosition().z + node->getSize()/2.))
            break;

        //Si il peut être contenu dans un des enfant.
        //On alloue l'enfant s'il n'existe pas.
        node->allocateChild(relPos);
        node = node->getChildren()[relPos] ;
    }
    //Si on est sur une feuille
    node->addObject(object);
    m_parents[object] = node;
    updateNodeSubdivision(node);
    //++m_objectCount;
    //cout << "nombre d'éléments de " << node << " après insertion : " << node->getObjects().size() << endl ;
}

void PWorld::updateObject(int object)
{
    if(m_parents[object] == nullptr)
        return;

       //Sinon, on supprime l'objet du noeud et on l'insère dans un noeud proche.
       removeObject(m_parents[object], object);
       addObject(m_root, object);
       //print(m_root);
}

void PWorld::addObjectOutsideWorld(int object)
{
    //On part de la racine
    Node* node = m_root ;
    //Tant que l'objet ne peut pas être contenu dans la racine
    while(node->getAABB().relativePosition(m_objects[object]->getAABB()) != INSIDE)
    {
        //On calcule la position relative du noeud courant et de l'objet.
        int relPos = 0;
        relPos += (m_objects[object]->getAABB().getBottomPosition() < node->getPosition().y) ? TOP : BOTTOM ;
        relPos += (m_objects[object]->getAABB().getLeftPosition() < node->getPosition().x) ? RIGHT : LEFT ;
        relPos += (m_objects[object]->getAABB().getBackPosition() < node->getPosition().z) ? FRONT : BACK ;

        //On calcule la position de la nouvelle racine.
        vec3 pos(node->getPosition().x - ((relPos&RIGHT) ? node->getSize() : 0.f),
                    node->getPosition().y - ((relPos&TOP) ? node->getSize() : 0.f),
                 node->getPosition().z - ((relPos&FRONT) ? node->getSize() : 0.f));

        //La racine devient enfant de la nouvelle.
        Node* parent = new Node(pos, node->getSize()*2.f, nullptr);
        node->setParent(parent);
        parent->setChild(relPos, node) ;
        updateNodeMerge(parent);
        node = parent ;
    }
    m_root = node ;
    addObject(m_root, object);
}

void PWorld::removeObject(PObject *object)
{
	int id = object->getId();
	object->setId(-1);
	(*m_objects.end())->setId(id);
    swap(m_parents[id], *m_parents.end());
    swap(m_objects[id], *m_objects.end());
	m_objects.pop_back();
	m_parents.pop_back();
    removeObject(m_parents[id], id);
}

void PWorld::removeObject(Node* node, int object)
{
    node->removeObject(object);
	m_parents[object] = nullptr;
    updateNodeMerge(node);
    updateRoot();
}

void PWorld::updateNodeMerge(Node* node)
{
    /**** HYPOTHESE POUR LA FUSION : LES ENFANTS SONT A JOUR *****/
    Node* current = node ;
    while(current != nullptr)
    {
        if(!current->hasChildren() && current->getObjectCount() == 0)
        {
            Node* n = current ;
            //parent existe ? (crash si supression du dernier object de la racine)
            current = current->getParent() ;
            current->setChild(n, nullptr) ;
            continue;
        }
        else if(current->hasChildren())
        {
            int objCount =  current->getObjectCount() ;
            for(int i = 0 ; i < 8 ; i++)
            {
                if(current->getChildren()[i] != nullptr)
                {
                    if(current->getChildren()[i]->hasChildren())
                        return;

                    objCount += current->getChildren()[i]->getObjectCount();
                }
            }

            if(objCount >= MIN_OBJECTS)
                return;

            //On fusionne.
            for(int i = 0 ; i < 8 ; i++)
            {
                if(current->getChildren()[i] != nullptr)
                {
                    for(auto it = current->getChildren()[i]->getObjects().begin() ; it != current->getChildren()[i]->getObjects().end() ; it++)
                    {
                        current->addObject(*it);
                        m_parents[*it] = current;
                    }
                    current->setChild(i, nullptr);
                }
            }
        }
        current = current->getParent();
    }
}

void PWorld::updateNodeSubdivision(Node* node)
{
    queue<Node*> q ;
    q.push(node);
    array<bool, 8> editedNode = {false}; 

    while(!q.empty())
    {
        Node* current = q.front();
        q.pop();
        if(!current->hasChildren() && current->getObjectCount() > MAX_OBJECTS)
        {
            for(auto it = current->getObjects().begin() ; it != current->getObjects().end() ; it++)
            {
                //On calcule la position relative du noeud courant et de l'objet.
                int relPos = 0;

                //On regarde si l'object est dans la partie haute.
                relPos += (m_objects[*it]->getAABB().getBottomPosition() > current->getPosition().y + current->getSize()/2.f) ? TOP : BOTTOM ;
                //S'il n'y est pas, on regarde s'il est aussi dans la partie basse
                if(!(relPos&TOP) && !(m_objects[*it]->getAABB().getTopPosition() < (current->getPosition().y + current->getSize()/2.f)))
                    continue;

                //On regarde si l'object est dans la partie droite.
                relPos += (m_objects[*it]->getAABB().getLeftPosition() > current->getPosition().x + current->getSize()/2.f) ? RIGHT : LEFT ;
                //S'il n'y est pas, on regarde s'il est aussi dans la partie gauche.
                if(!(relPos&RIGHT) && !(m_objects[*it]->getAABB().getRightPosition() < (current->getPosition().x + current->getSize()/2.f)))
                    continue;

                //On regarde si l'object est dans la partie devant.
                relPos += (m_objects[*it]->getAABB().getBackPosition() > current->getPosition().z + current->getSize()/2.f) ? FRONT : BACK ;
                //S'il n'y est pas, on regarde s'il est aussi dans la partie derriere.
                if(!(relPos&FRONT) && !(m_objects[*it]->getAABB().getFrontPosition() < (current->getPosition().z + current->getSize()/2.f)))
                    continue;

                //Si il peut être contenu dans un des enfant.
                //On alloue l'enfant s'il n'existe pas.
                current->allocateChild(relPos);                 

                //On l'ajoute.
                current->getChildren()[relPos]->addObject(*it);
                m_parents[*it] = current->getChildren()[relPos] ;

                editedNode[relPos] = true ;

                //On l'enleve du noeud.
				//OPTIMIZE ME
                //current->m_objects.erase(it++);
				current->removeObject(*(it++));
            }
            for(int i = 0 ; i < 8 ; i++)
            {
                if(editedNode[i])
                {
                    q.push(current->getChildren()[i]);
                    editedNode[i] = false ;
                }
            }
        }
    }

}
void PWorld::updateRoot()
{
    Node* temp ;
    while(m_root->getChildrenCount() == 1 && m_root->getObjectCount() == 0)
    {
        for(int i = 0 ; i < 8 ; i++)
        {
            if(m_root->getChildren()[i] != nullptr)
            {
                temp = m_root->getChildren()[i] ;
                m_root->disconnect() ;
				delete m_root;
                m_root = temp ;
                m_root->setParent(nullptr);
                break;
            }
        }
    }
}
void PWorld::update(float step)
{
    chrono::time_point<chrono::system_clock> begin, par, broad, narrow, col, end;
    begin = chrono::system_clock::now();

 
    PObject* obj ;
    stack<Node*> s;

    if(m_root != nullptr)
        s.push(m_root);

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
            obj = m_objects[*it] ;

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
    queue<pair<Node*, list<int>&>> s;
	
    if(m_root != nullptr)
        s.push({m_root, *new list<int>()});

    while(!s.empty())
    {
        Node* node = s.front().first;
        list<int>& parentObjects = s.front().second;
        //tie(node, parentObjects) = s.top();

        //Pour chaque objet, on cherche une collision potentielle.
        for (auto it = node->getObjects().begin(); it != node->getObjects().end(); it++)
        {
            //Avec les objets du noeud.
            for (auto jt = node->getObjects().begin(); jt != it; jt++)
            {
                const Geometry *g1 = &m_objects[*it]->getGeometry(), *g2 = &m_objects[*jt]->getGeometry();
                if (g1->getBoundingSphere().collide(g2->getBoundingSphere()))
                    m_potentialCollisions.push_back({*it, *jt});
            }
            //Avec les objets passé par le parent.
            for (auto kt = parentObjects.begin(); kt != parentObjects.end() ; kt++)
            {
                const Geometry *g1 = &m_objects[*it]->getGeometry(), *g2 = &m_objects[*kt]->getGeometry();
                if (g1->getBoundingSphere().collide(g2->getBoundingSphere()))
                    m_potentialCollisions.push_back({*it, *kt});
            }
            
        }

        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                //On détermine les objets a passer.
                list<int>& objects = *new list<int>();
                for(auto it = parentObjects.begin() ; it != parentObjects.end() ; it++)
                {
                    if(node->getChildren()[i]->getAABB().relativePosition(m_objects[*it]->getAABB()) != OUTSIDE)
                        objects.push_back(*it);
                }
                for(auto it = node->getObjects().begin() ; it != node->getObjects().end() ; it++)
                {
                    if(node->getChildren()[i]->getAABB().relativePosition(m_objects[*it]->getAABB()) != OUTSIDE)
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
    int obj1, obj2 ;
    for (auto it = m_potentialCollisions.begin(); it != m_potentialCollisions.end(); it++)
    {
        obj1 = (*it)[0];
        obj2 = (*it)[1];
        if(m_objects[obj1]->getGeometry().collide(&(m_objects[obj2]->getGeometry())))
        {
            Contact* c = m_objects[obj1]->getGeometry().collisionPoints(&(m_objects[obj2]->getGeometry()));
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
    impulses.resize(m_objects.size());
    vector<vec3> positions;
    positions.resize(m_objects.size());


    int obj1, obj2;
    vec3 normal, point ;
    for (int i = 0 ; i < 1 ; i++) 
    {
        for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
        {
            obj1 = get<1>(*it);
            obj2 = get<2>(*it);
            Contact* c = get<0>((*it));
            vec3 impulse = c->solvePosition(m_objects[obj1], m_objects[obj2]);

       
        }
    }

    for (int i = 0 ; i < 50 ; i++) 
    {
        for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
        {
            obj1 = get<1>(*it);
            obj2 = get<2>(*it);
            Contact* c = get<0>((*it));
            vec3 impulse = c->solveImpulse(m_objects[obj1], m_objects[obj2]);
       
        }
    }
    for(auto it = m_contacts.begin() ; it != m_contacts.end(); it++)
    {
        delete get<0>(*it);
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
    cout << m_objects.size() << "objets" << endl;
    for(auto it = m_objects.begin() ; it != m_objects.end() ; it++)
    {
        PObject* obj = *it;
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

	if (obj->getId() < 0)
		return;

    updateObject(obj->getId());
}
const Node* PWorld::getOctree() const
{
    return m_root ;
}
/*
void Octree::print(Node* node) const
{
    cout << endl ;
    queue<pair<Node*, bool>> q ;
    q.push({node, true});
    while(!q.empty())
    {
        Node* node ;
        bool endline = true;
        std::tie(node, endline) = q.front() ;
        q.pop();
        for(int i = 0 ; i < 8 ; i++)
        {
            if(node->getChildren()[i] != nullptr)
            {
                q.push({node->getChildren()[i], false});
            }
        }
        get<1>(q.back()) = true ;
        cout << node << "(objets:" << node->getObjects().size() << ", " << "enfants : " << node->m_childrenCount << " , " ;
        if(!node->hasChildren())
            cout << "not " ;
        cout << "divided) ; " ;
        if(endline)
            cout << endl ;
    }
    cout << endl << endl ;
}
*/
