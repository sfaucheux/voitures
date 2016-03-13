#include "octree.h"

using namespace glm;
Octree::Octree()
{
    m_root = nullptr;
}
Octree::~Octree()
{
    if(m_root != nullptr)
        delete m_root;
}
Node* Octree::addObject(PObject* obj)
{
    //Si le monde est vide, on le créé autour de l'objet.
    if(m_root == nullptr)
    {
        vec3 objSize = obj->getAABB().getSize() ;
        float size = 2*std::max(std::max(objSize.x,objSize.y),objSize.z);
        m_root = new Node(obj->getPosition() - 0.5f*objSize, size, nullptr);
    }
    //On ajoute l'objet à la racine.
    return addObject(m_root, obj);
}
Node* Octree::addObject(Node* n, PObject* obj)
{
    Node* node = n;
    //On cherche le noeud qui puisse contenir l'objet.
    //On commence sur le noeud courant et on remonte jusqu'à la racine.
    while(node->getAABB().relativePosition(obj->getAABB()) != INSIDE && node != nullptr )
    {
        node = node->getParent() ;
    }
    //Si on on a trouvé un parent capable de contenir l'objet.
    //Phase de redescente.
    if(node != nullptr)
    {   
        return addObjectToChildren(node, obj);
    }
    //Sinon le monde n'est pas assez grand, on l'agrandi.
    addObjectOutsideWorld(obj);
    return m_root ;

}
Node* Octree::addObjectToChildren(Node* node, PObject* obj)
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
                node->addObject(obj);
                return node ;
            }
        }
    }

}
Node* Octree::updateObject(Node* node, PObject* obj)
{
   //Si l'objet est  déjà dans le bon noeud, on le retourne.
   if(node->getAABB().relativePosition(obj->getAABB()) == INSIDE)
        return node ;
   //Sinon, on supprime l'objet du noeud et on l'insère dans un noeud proche.
   node->removeObject(obj);
   return addObject(node->getParent(), obj);
    
}
void Octree::addObjectOutsideWorld(PObject* obj)
{
    //On part de la racine
    Node* node = m_root ;
    //Tant que l'objet ne peut pas être contenu dans la racine
    while(node->getAABB().relativePosition(obj->getAABB()) != INSIDE)
    {
        //On calcule la position relative du noeud courant et de l'objet.
        int relPos = 0;
        relPos += (obj->getAABB().getBottomPosition() < node->getPosition().y) ? TOP : BOTTOM ;
        relPos += (obj->getAABB().getLeftPosition() < node->getPosition().x) ? RIGHT : LEFT ;
        relPos += (obj->getAABB().getBackPosition() < node->getPosition().z) ? FRONT : BACK ;

        //On calcule la position de la nouvelle racine.
        vec3 pos(node->getPosition().y - ((relPos&TOP) ? node->getSize() : 0),
                 node->getPosition().x - ((relPos&RIGHT) ? node->getSize() : 0),
                 node->getPosition().z - ((relPos&FRONT) ? node->getSize() : 0));

        //La racine devient enfant de la nouvelle.
        Node* parent = new Node(pos, node->getSize()*2, nullptr);
        node->setParent(parent);
        parent->getChildren()[relPos] = node ;
        node = parent ;
    }
    m_root = node ;
}
void Octree::removeObject(Node* node, PObject* obj)
{
    node->removeObject(obj);
}
void Octree::setRoot(Node* root)
{
    m_root = root;
}

Node* Octree::getRoot() const
{
    return m_root ;
}
