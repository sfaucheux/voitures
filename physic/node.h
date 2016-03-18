#ifndef NODE_H
#define NODE_H

#include <array>
#include <list>
#include "../glm/glm.hpp"
#include "pobject.h"
#include "../geometry/aabb.h"

        enum X_POS {LEFT = 0, RIGHT = 1};
        enum Y_POS {BOTTOM = 0, TOP = 2};
        enum Z_POS {BACK = 0, FRONT = 4};

class Node {
    public:
        //MAX > MIN
        static const unsigned int MAX_OBJECTS = 50;
        static const unsigned int MIN_OBJECTS = 3;

        Node(glm::vec3 pos, float size, Node* parent = nullptr);
        ~Node();

        float getSize() const;
        glm::vec3 getPosition() const;
        Node* getParent() const;
        std::array<Node*, 8> getChildren() const;
        const std::list<PObject*>& getObjects() const;
        unsigned int getObjectCount() const;

        bool hasChildren() const;
        AABB getAABB() const ;

        void setParent(Node* parent);
        void setObjectCount(unsigned int c);

        void addObject(PObject*) ;
        void removeObject(PObject*) ;

        void setChild(unsigned int ch, Node* node);

        void allocateChild(unsigned int pos);

    private:
        void update();

        glm::vec3 m_position ;
        float m_size ;
        Node* m_parent ;
        std::array<Node*, 8> m_children ;
        std::list<PObject*> m_objects ;
        unsigned int m_objectCount ;
        unsigned int m_childrenCount ;

};

#endif
