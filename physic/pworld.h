#ifndef PWorld_H
#define PWorld_H

#include <list>
#include <array>

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

        std::list<PObject*> m_objects;
        glm::vec3 m_gravity;
        std::list<std::array<PObject*,2>> m_potentialCollisions;
        std::list<PObject*> m_collided;

};

#endif
