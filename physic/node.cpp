#include "octree.h"
#include <stack>
#include <iostream>

using namespace glm ;
using namespace std ;

Node::Node(vec3 pos, float size, Node* parent)
{
    m_parent = parent;
    m_children = {nullptr};
    m_objectCount = 0;
    m_position = pos ;
    m_size = size;
    m_childrenCount = 0;
}
Node::~Node()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] != nullptr)
            delete m_children[i];
    }
}
Node* Node::getParent() const
{
    return m_parent;
}
AABB Node::getAABB() const
{
    return AABB(vec3(m_size), m_position + vec3(m_size/2.f)) ;
}
float Node::getSize() const
{
    return m_size ;
}
vec3 Node::getPosition() const
{
    return m_position ;
}
void Node::removeObject(PObject* obj)
{
    m_objects.remove(obj);
    obj->setNode(nullptr);
    Node* node = m_parent;
    while(node != nullptr)
    {
        node->setObjectCount(node->getObjectCount() - 1);
        node = node->getParent();
    }
    update();
}
void Node::addObject(PObject* obj)
{
    cout << "ajout dans " << this << endl ;
    m_objects.push_back(obj);
    obj->setNode(this);
    Node* node = m_parent;
    while(node != nullptr)
    {
        node->setObjectCount(node->getObjectCount() + 1);
        node = node->getParent() ;
    }
    update();
}
void Node::setParent(Node* parent)
{
    Node* node = m_parent ;
    while(node != nullptr)
    {
        node->setObjectCount(node->getObjectCount() - m_objectCount - m_objects.size());
        node = node->getParent();
    }
    node = parent ;
    while(node != nullptr)
    {
        cout << "nouveau parent : +" << m_objectCount + m_objects.size() << " sur " << node << endl;
        node->setObjectCount(node->getObjectCount() + m_objectCount + m_objects.size());
        node = node->getParent();
    }
    m_parent = parent ;
}
bool Node::hasChildren() const
{
    return m_childrenCount ;
}
std::array<Node*,8> Node::getChildren() const
{
    return m_children;
}

void Node::setObjectCount(unsigned int c)
{
    m_objectCount = c;
    update();
}
unsigned int Node::getObjectCount() const
{
    return m_objectCount;
}
const std::list<PObject*>& Node::getObjects() const
{
    return m_objects;
}
void Node::allocateChild(unsigned int relPos)
{
    //On alloue l'enfant s'il n'existe pas.
    if(m_children[relPos] == nullptr)
    {
        //On calcule la position de l'enfant.
        vec3 pos(m_position.x + ((relPos&RIGHT) ? m_size/2.f : 0.f),
                m_position.y + ((relPos&TOP) ? m_size/2.f : 0.f),
                m_position.z + ((relPos&FRONT) ? m_size/2.f : 0.f));

        m_children[relPos] = new Node(pos, m_size/2.f, this);
        m_childrenCount++;
    }

}
void Node::setChild(unsigned int ch, Node* node)
{
    if(m_children[ch] != nullptr)
        delete m_children[ch] ;
    else
    {
        m_childrenCount++;
    }

    m_children[ch] = node ;
}
void Node::update()
{
    if(m_objects.size() > MAX_OBJECTS && !hasChildren())
    {
        cout << "subdivision de " << this << endl ;
        for(auto it = m_objects.begin() ; it != m_objects.end() ; it++)
        {
            //On calcule la position relative du noeud courant et de l'objet.
            int relPos = 0;

            //On regarde si l'object est dans la partie haute.
            relPos += ((*it)->getAABB().getBottomPosition() > m_position.y + m_size/2.f) ? TOP : BOTTOM ;
            //S'il n'y est pas, on regarde s'il est aussi dans la partie basse
            if(!(relPos&TOP) && !((*it)->getAABB().getTopPosition() < (m_position.y + m_size/2.f)))
                continue;

            //On regarde si l'object est dans la partie droite.
            relPos += ((*it)->getAABB().getLeftPosition() > m_position.x + m_size/2.f) ? RIGHT : LEFT ;
            //S'il n'y est pas, on regarde s'il est aussi dans la partie gauche.
            if(!(relPos&RIGHT) && !((*it)->getAABB().getRightPosition() < (m_position.x + m_size/2.f)))
                continue;

            //On regarde si l'object est dans la partie devant.
            relPos += ((*it)->getAABB().getBackPosition() > m_position.z + m_size/2.f) ? FRONT : BACK ;
            //S'il n'y est pas, on regarde s'il est aussi dans la partie derriere.
            if(!(relPos&LEFT) && !((*it)->getAABB().getFrontPosition() < (m_position.z + m_size/2.f)))
                continue;

            //Si il peut être contenu dans un des enfant.
            cout << "il est possible de stocker dans un enfant : "<< relPos << endl ;
            //On alloue l'enfant s'il n'existe pas.
            allocateChild(relPos);            

            //On l'ajoute.
            //FIXME addObject fait +1 sur tous les parents.
            PObject* obj = *it ;
            it++;
            removeObject(obj);
            m_children[relPos]->addObject(obj);
            //On l'enleve du noeud.
            //it = m_objects.erase(it);
        }
    }
    if(m_objectCount + m_objects.size() < MIN_OBJECTS && hasChildren())
    {
        cout << "fusion" << endl ;
        //On fusionne.
        for(int i = 0 ; i < 8 ; i++)
        {
            if(m_children[i] != nullptr)
            {
                for(auto it = m_children[i]->getObjects().begin() ; it != m_children[i]->getObjects().end() ; it++)
                {
                    m_objects.push_back(*it);
                    (*it)->setNode(this);
                }
                delete m_children[i];
                m_children[i] = nullptr;
            }
        }
        m_childrenCount = 0;
        m_objectCount = 0;
    }

}
