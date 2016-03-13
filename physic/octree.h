#ifndef OCTREE_H
#define OCTREE_H

#include "node.h"

class Octree {
    public:
        Octree();
        ~Octree();

        Node* getRoot() const;

        Node* addObject(PObject* obj);
        Node* addObject(Node* node, PObject* obj);
        Node* updateObject(Node* node, PObject* obj);
        void removeObject(Node* node, PObject* obj);

        void setRoot(Node* root) ;

    private:
        Node* m_root ;
        Node* addObjectToChildren(Node* node, PObject* obj);
        void addObjectOutsideWorld(PObject* obj);

};

#endif
