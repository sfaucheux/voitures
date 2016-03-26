#include "octree.h"
#include <stack>
#include <iostream>

using namespace glm ;
using namespace std ;

Node::Node(vec3 pos, float size, Node* parent)
{
    m_parent = parent;
    m_children = {nullptr};
    m_childrenCount = 0;
    m_position = pos ;
    m_size = size;
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
}
void Node::addObject(PObject* obj)
{
    m_objects.push_back(obj);
    obj->setNode(this);
}
void Node::setParent(Node* parent)
{
    m_parent = parent ;
}
bool Node::hasChildren() const
{
    return m_childrenCount ;
}
const std::array<Node*,8>& Node::getChildren() const
{
    return m_children;
}

unsigned int Node::getObjectCount() const
{
    return m_objects.size();
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
    {
        delete m_children[ch] ;
        m_childrenCount--;
    }
    if(node != nullptr)
    {
        m_childrenCount++;
    }
    m_children[ch] = node ;
}

void Node::setChild(Node* oldNode, Node* newNode)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] == oldNode)
        {
            setChild(i, newNode);
            return;
        }
    }
}

