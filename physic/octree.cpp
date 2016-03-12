#include "octree.h"
#include <stack>

using namespace glm ;

Octree::Octree(vec3 pos, float size, Octree* parent)
{
    m_parent = nullptr;
    m_children = {nullptr};
    m_objectCount = 0;
    m_position = pos ;
    m_size = size;
}
Octree::~Octree()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] != nullptr)
            delete m_children[i];
    }
}
void Octree::addObject(PObject* obj)
{
    Octree* node = this;
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
            Octree* parent = new Octree(pos, node->getSize()*2, nullptr);
            node->setParent(parent);
            node = parent ;
        }
    }
}
Octree* Octree::getParent() const
{
    return m_parent;
}
AABB Octree::getAABB() const
{
    return AABB(vec3(m_size), m_position + vec3(m_size/2)) ;
}
float Octree::getSize() const
{
    return m_size ;
}
vec3 Octree::getPosition() const
{
    return m_position ;
}
void Octree::removeObject(PObject*)
{

}
void Octree::updateObject(PObject*)
{

}
void Octree::addObjectInNode(PObject* obj)
{
    m_objects.push_back(obj);
    m_objectCount++;
    //obj->setNode(this);
}
void Octree::subdivise()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] == nullptr)
            m_children[i] = new Octree(m_position + m_size/2*vec3(i&1, i&2, i&4), m_size/2, this) ;
    }
}
void Octree::setParent(Octree* parent)
{
    m_parent = parent ;
}
bool Octree::hasChildren() const
{
    return m_children[0] != nullptr ;
}
std::array<Octree*,8> Octree::getChildren() const
{
    return m_children;
}
