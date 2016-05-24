#ifndef PWorld_H
#define PWorld_H

#include <list>
#include <array>
#include <set>
#include <tuple>
#include <stack>

#include "../glm/glm.hpp"

#include "pobject.h"
#include "octree.h"
#include "../collision/contact.h"

class PWorld 
{
    public:
        PWorld(glm::vec3 gravity);
        void setGravity(glm::vec3 gravity);
        void update(float step);
        void addObject(PObject*);
        void updateObject(PObject*);
        void translateObject(PObject* obj, glm::vec3 t);
        void removeObject(PObject*);

        const Octree& getOctree() const;


    private:
        void integrate(float step);
        void broadPhase();
        void narrowPhase();
        void collisionResponse();
        glm::vec3 computeImpulse(PObject* obj1, PObject* obj2, glm::vec3 point, glm::vec3 normal);

        Octree m_octree;
        glm::vec3 m_gravity;
        std::vector<std::array<PObject*,2>> m_potentialCollisions;
        std::vector<std::tuple<Contact*, PObject*, PObject*>> m_contacts ;
};

#endif
