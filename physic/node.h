#ifndef NODE_H
#define NODE_H

#include <array>
#include <list>
#include "../glm/glm.hpp"
#include "../geometry/aabb.h"

        enum X_POS {LEFT = 0, RIGHT = 1};
        enum Y_POS {BOTTOM = 0, TOP = 2};
        enum Z_POS {BACK = 0, FRONT = 4};

class Node {
    friend class PWorld;
    public:
        float getSize() const;
        glm::vec3 getPosition() const;
        Node* getParent() const;
        unsigned int getObjectCount() const;
        bool hasChildren() const;
        AABB getAABB() const ;
        const std::array<Node*, 8>& getChildren() const;
        const std::list<int>& getObjects() const;

    private:
        Node(glm::vec3 pos, float size, Node* parent = nullptr);
        ~Node();

        void setParent(Node* parent);

        void addObject(int);
        void removeObject(int);

        void setChild(unsigned int ch, Node* node);
        void setChild(Node* oldNode, Node* newNode);

        void allocateChild(unsigned int pos);

        glm::vec3 m_position ;
        float m_size ;
        Node* m_parent ;
        std::array<Node*, 8> m_children ;
        std::list<int> m_objects ;
        unsigned int m_childrenCount ;

};

#endif
