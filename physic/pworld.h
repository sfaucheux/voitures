#ifndef PWorld_H
#define PWorld_H

#include <list>
#include <array>
#include <set>
#include <tuple>

#include "../glm/glm.hpp"

#include "pobject.h"

class PWorld 
{
    public:
        PWorld(glm::vec3 gravity);
        void setGravity(glm::vec3 gravity);
        void update(float step);
        void addObject(PObject*);
        void removeObject(PObject*);


    private:
        void integrate(float step);
        void broadPhase();
        void narrowPhase();
        void collisionResponse();
        glm::vec3 computeImpulse(PObject* obj1, PObject* obj2, glm::vec3 point, glm::vec3 normal);

        std::list<PObject*> m_objects;
        glm::vec3 m_gravity;
        std::list<std::array<PObject*,2>> m_potentialCollisions;
        std::list<std::tuple<PObject*, PObject*, std::vector<std::tuple<glm::vec3, glm::vec3>>>> m_contacts ;
};

#endif
