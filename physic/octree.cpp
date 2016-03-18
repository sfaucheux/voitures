#include "octree.h"
#include <iostream>
#include <queue>

using namespace std;
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
void Octree::addObject(PObject* obj)
{
    //cout << "ajout d'un objet à la racine" << endl ;
    //cout << "racine : " << m_root << endl ;
    //Si le monde est vide, on le créé autour de l'objet.
    if(m_root == nullptr)
    {
        cout << "creation du monde" << endl ;
        vec3 objSize = obj->getAABB().getSize() ;
        float size = 2.5f*std::max(std::max(objSize.x,objSize.y),objSize.z);
        m_root = new Node(obj->getPosition() - 1.5f*objSize, size, nullptr);
        vec3 pos = m_root->getPosition() ;
    }
    //On ajoute l'objet à la racine.
    addObject(m_root, obj);
}
void Octree::addObject(Node* n, PObject* obj)
{
    cout << "ajout d'un objet au niveau d'un noeud : " << m_root << endl;
    Node* node = n;
    //On cherche le noeud qui puisse contenir l'objet.
    //On commence sur le noeud courant et on remonte jusqu'à la racine.
    while(node != nullptr && node->getAABB().relativePosition(obj->getAABB()) != INSIDE)
    {
        node = node->getParent() ;
    }
    //Si on on a trouvé un parent capable de contenir l'objet.
    //Phase de redescente.
    if(node != nullptr)
    {   
        //cout << "noeud capable de contenir l'objet" << endl ;
        addObjectToChildren(node, obj);
        return;
    }
    //Sinon le monde n'est pas assez grand, on l'agrandi.
    //cout << "pas de noeud capable de contenir l'objet" << endl ;
    addObjectOutsideWorld(obj);
}

void Octree::addObjectToChildren(Node* node, PObject* obj)
{
    //cout << "ajout d'un objet DANS le noeud spécifié" << endl ;
    /*
    Node* parent = node->getParent();
    //On incrémente la taille des parents
    while(parent != nullptr)
    {
        //node->setObjectCount(node->getObjectCount() + 1);
        parent = node->getParent();
    }*/
    while(node->hasChildren())
    {
        //On calcule la position relative du noeud courant et de l'objet.
        int relPos = 0;

        //On regarde si l'object est dans la partie haute.
        relPos += (obj->getAABB().getBottomPosition() > node->getPosition().y + node->getSize()/2.) ? TOP : BOTTOM ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie basse
        if(!(relPos&TOP) && !(obj->getAABB().getTopPosition() < node->getPosition().y + node->getSize()/2.))
            break;

        //On regarde si l'object est dans la partie droite.
        relPos += (obj->getAABB().getLeftPosition() > node->getPosition().x + node->getSize()/2.) ? RIGHT : LEFT ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie gauche.
        if(!(relPos&RIGHT) && !(obj->getAABB().getRightPosition() < node->getPosition().x + node->getSize()/2.))
            break;

        //On regarde si l'object est dans la partie devant.
        relPos += (obj->getAABB().getBackPosition() > node->getPosition().z + node->getSize()/2.) ? FRONT : BACK ;
        //S'il n'y est pas, on regarde s'il est aussi dans la partie derriere.
        if(!(relPos&FRONT) && !(obj->getAABB().getFrontPosition() < node->getPosition().z + node->getSize()/2.))
            break;

        //Si il peut être contenu dans un des enfant.
        cout << "allocation d'un enfant." << endl ;

        //On alloue l'enfant s'il n'existe pas.
        node->allocateChild(relPos);
        node = node->getChildren()[relPos] ;
    }
    //Si on est sur une feuille
    node->addObject(obj);
    //cout << "nombre d'éléments de " << node << " après insertion : " << node->getObjects().size() << endl ;
}

void Octree::updateObject(PObject* obj)
{
    if(obj->getNode() == nullptr)
        return;

   //Si l'objet est  déjà dans le bon noeud, on le retourne.
   if(obj->getNode()->getAABB().relativePosition(obj->getAABB()) == INSIDE)
        return ;

   //Sinon, on supprime l'objet du noeud et on l'insère dans un noeud proche.
   obj->getNode()->removeObject(obj);
   addObject(obj->getNode(), obj);
}

void Octree::addObjectOutsideWorld(PObject* obj)
{
    cout << "on agrandi le monde !" << endl ;
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
        vec3 pos(node->getPosition().x - ((relPos&RIGHT) ? node->getSize() : 0.f),
                    node->getPosition().y - ((relPos&TOP) ? node->getSize() : 0.f),
                 node->getPosition().z - ((relPos&FRONT) ? node->getSize() : 0.f));

        //La racine devient enfant de la nouvelle.
        Node* parent = new Node(pos, node->getSize()*2.f, nullptr);
        pos = parent->getPosition() ;
        node->setParent(parent);
        parent->setChild(relPos, node) ;
        node = parent ;
    }
    m_root = node ;

    addObject(m_root, obj);
    //node->setObjectCount(node->getObjectCount() + 1);
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
void Octree::afficher(Node* node) const
{
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
        cout << node << "(objets:" << node->getObjects().size() << " total:" << node->getObjects().size() + node->getObjectCount() << " , " ;
        if(!node->hasChildren())
            cout << "not " ;
        cout << "divided) ; " ;
        if(endline)
            cout << endl ;
    }
    cout << endl ;
}
