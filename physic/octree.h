#ifndef OCTREE_H
#define OCTREE_H

#include "node.h"

class Octree {
    public:
        Octree();
        ~Octree();

        Node* getRoot() const;

        void addObject(PObject* obj);
        void addObject(Node* node, PObject* obj);
        void updateObject(PObject* obj);
        void removeObject(Node* node, PObject* obj);

        void setRoot(Node* root) ;
        void afficher(Node* node) const;

    private:
        Node* m_root ;
        void addObjectToChildren(Node* node, PObject* obj);
        void addObjectOutsideWorld(PObject* obj);

};

#endif
