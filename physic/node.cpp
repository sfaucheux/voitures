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
void Node::addObject(PObject* obj)
{
    m_objects.push_back(obj);
    m_objectCount++;
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
void Node::update()
{
    if(m_childCount == 0 && m_objectCount < MIN_OBJECTS)
    {

    }
}
