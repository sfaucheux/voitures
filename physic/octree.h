#ifndef OCTREE_H
#define OCTREE_H

#include <array>
#include <list>
#include "../glm/glm.hpp"
#include "pobject.h"
#include "aabb.h"

class Octree {
    public:
        /* D/U : Down/Up ; L/F : Left/Right ; B/F : Back/Front */
        enum POSITION {DLB = 0, DRB, DLF, DRF, ULB, URB, ULF, URF};
        static const unsigned int MAX_OBJECTS = 16;
        static const unsigned int MIN_OBJECTS = 0 ;
        Octree(glm::vec3 pos, float size, Octree* parent = nullptr);
        ~Octree();

        glm::vec3 getPosition() const ;
        float getSize() const ;
        Octree* getParent() const ;
        std::array<Octree*, 8> getChildren();
        AABB getAABB() const ;


        void addObject(PObject*) ;
        void addObjectInNode(PObject*)
        void removeObject(PObject*) ;
        void updateObject(PObject*) ;

    private:
        void subdivise();

        glm::vec3 m_postion ;
        float m_size ;
        Octree* parent ;
        std::array<Octree*, 8> m_children ;
        std::list<PObject*> m_objects ;
        unsigned int m_objectCount ;
}

#endif
