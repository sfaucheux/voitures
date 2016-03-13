#include "octree.h"
#include <stack>

using namespace glm ;

Node::Node(vec3 pos, float size, Node* parent)
{
    m_parent = nullptr;
    m_children = {nullptr};
    m_objectCount = 0;
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
void Node::addObject(PObject* obj)
{
    Node* node = this;
    //On cherche le noeud qui puisse contenir l'objet.
    //On commence sur le noeud courant et on remonte jusqu'à la racine.
    while(node->getAABB().relativePosition(obj->getAABB()) == INSIDE && node->getParent() != nullptr )
    {
        node = node->getParent() ;
    }
    //Si on on a trouvé un parent capable de contenir l'objet.
    //Phase de redescente.
    if(node->getAABB().relativePosition(obj->getAABB()) == INSIDE)
    {   
        while(node->hasChildren())
        {
            for(int i = 0; i < 8 ; i++)
            {
                RESULT result = node->getChildren()[i]->getAABB().relativePosition(obj->getAABB()) ;
                if(result == INSIDE)
                {
                    node = node->getChildren()[i] ;
                    break;
                }
                else if(result == INTERSECT)
                {
                    //On ajoute l'objet au noeud.
                    node->addObjectInNode(obj);
                    return;
                }
            }
        }
    }
    //Sinon le monde n'est pas assez grand, on l'agrandi.
    else
    {
        while(node->getAABB().relativePosition(obj->getAABB()) == INSIDE)
        {
            int relPos = 0;
            relPos += (obj->getAABB().getBottomPosition() < node->getPosition().y) ? TOP : BOTTOM ;
            relPos += (obj->getAABB().getLeftPosition() < node->getPosition().x) ? RIGHT : LEFT ;
            relPos += (obj->getAABB().getBackPosition() < node->getPosition().z) ? FRONT : BACK ;
            vec3 pos(node->getPosition().x - (relPos&TOP) ? node->getSize() : 0,
                     node->getPosition().y - (relPos&RIGHT) ? node->getSize() : 0,
                     node->getPosition().z - (relPos&FRONT) ? node->getSize() : 0);
            Node* parent = new Node(pos, node->getSize()*2, nullptr);
            node->setParent(parent);
            node = parent ;
        }
    }
}
Node* Node::getParent() const
{
    return m_parent;
}
AABB Node::getAABB() const
{
    return AABB(vec3(m_size), m_position + vec3(m_size/2)) ;
}
float Node::getSize() const
{
    return m_size ;
}
vec3 Node::getPosition() const
{
    return m_position ;
}
void Node::removeObject(PObject*)
{

}
void Node::updateObject(PObject*)
{

}
void Node::addObjectInNode(PObject* obj)
{
    m_objects.push_back(obj);
    m_objectCount++;
    //obj->setNode(this);
}
void Node::subdivise()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] == nullptr)
            m_children[i] = new Node(m_position + m_size/2*vec3(i&1, i&2, i&4), m_size/2, this) ;
    }
}
void Node::setParent(Node* parent)
{
    m_parent = parent ;
}
bool Node::hasChildren() const
{
    return m_children[0] != nullptr ;
}
std::array<Node*,8> Node::getChildren() const
{
    return m_children;
}
