#ifndef OCTREE_H
#define OCTREE_H

#include <array>
#include <list>
#include "../glm/glm.hpp"
#include "pobject.h"
#include "../geometry/aabb.h"

class Octree {
    public:
        enum X_POS {LEFT = 0, RIGHT = 1};
        enum Y_POS {BOTTOM = 0, TOP = 2};
        enum Z_POS {BACK = 0, FRONT = 4};

        static const unsigned int MAX_OBJECTS = 16;
        static const unsigned int MIN_OBJECTS = 0 ;
        Octree(glm::vec3 pos, float size, Octree* parent = nullptr);
        ~Octree();

        glm::vec3 getPosition() const ;
        float getSize() const ;
        Octree* getParent() const ;
        bool hasChildren() const;
        std::array<Octree*, 8> getChildren() const;
        AABB getAABB() const ;

        void setParent(Octree* parent);

        void addObject(PObject*) ;
        void addObjectInNode(PObject*);
        void removeObject(PObject*) ;
        void updateObject(PObject*) ;

    private:
        void subdivise();

        glm::vec3 m_position ;
        float m_size ;
        Octree* m_parent ;
        std::array<Octree*, 8> m_children ;
        std::list<PObject*> m_objects ;
        unsigned int m_objectCount ;
};

#endif
