#include "octree.h"

#include <stack>

Octree(glm::vec3 pos, glm::vec3 size, Octree* parent = nullptr)
{
    m_parent = nullptr;
    m_children = {nullptr};
    m_objectCount = 0;
    m_position(pos);
    m_size(size);
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
    while(node->getAABB().collide(obj->getAABB()) == AABB::INSIDE && node->getParent() != nullptr )
    {
        node = node->getParent() ;
    }
    //Si on on a trouvé un parent capable de contenir l'objet.
    //Phase de redescente.
    if(node->getAABB().collide(obj.getAABB()) == AABB::INSIDE)
    {   
        bool ok = true; 
        while(ok) //Arreter quand feuille
        {
            for(int i = 0; i < 8 ; i++)
            {
                result = node.getChildren()[i]->getAABB().collide(obj.getAABB()) ;
                if(result == INSIDE)
                {
                    node = node.getChildren()[i] ;
                    break;
                }
                else if(result == INTERSECT)
                {
                    //On ajoute l'objet au noeud.
                    node->addObjectInNode(obj);
                    ok = false;   
                }
            }
        }
    }
    //Sinon le monde n'est pas assez grand, on l'agrandi.
    else
    {
        while(node->getAABB().collide(obj.getAABB == AABB::INSIDE))
        {
            Octree* parent = new Octree()
            node->set
        }
    }
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
    //TODO
    //obj->setNode(this);
}
void Octree::subdivise()
{
    for(int i = 0 ; i < 8 ; i++)
    {
        if(m_children[i] == nullptr)
            m_children[i] = new Octree ;
    }
}
