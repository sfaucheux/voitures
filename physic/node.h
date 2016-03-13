#ifndef NODE_H
#define NODE_H

#include <array>
#include <list>
#include "../glm/glm.hpp"
#include "pobject.h"
#include "../geometry/aabb.h"

class Node {
    public:
        enum X_POS {LEFT = 0, RIGHT = 1};
        enum Y_POS {BOTTOM = 0, TOP = 2};
        enum Z_POS {BACK = 0, FRONT = 4};

        static const unsigned int MAX_OBJECTS = 16;
        static const unsigned int MIN_OBJECTS = 0 ;
        Node(glm::vec3 pos, float size, Node* parent = nullptr);
        ~Node();

        glm::vec3 getPosition() const ;
        float getSize() const ;
        Node* getParent() const ;
        bool hasChildren() const;
        std::array<Node*, 8> getChildren() const;
        AABB getAABB() const ;

        void setParent(Node* parent);

        void addObject(PObject*) ;
        void addObjectInNode(PObject*);
        void removeObject(PObject*) ;
        void updateObject(PObject*) ;

    private:
        void subdivise();

        glm::vec3 m_position ;
        float m_size ;
        Node* m_parent ;
        std::array<Node*, 8> m_children ;
        std::list<PObject*> m_objects ;
        unsigned int m_objectCount ;
};

#endif
