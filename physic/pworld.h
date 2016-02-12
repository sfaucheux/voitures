#ifndef PWorld_H
#define PWorld_H

#include <list>

#include "../glm/glm.hpp"

#include "pobject.h"
#include <array>

class PWorld 
{
    public:
        PWorld(glm::vec3 gravity);
        void setGravity(glm::vec3 gravity);
        void update(float step);
        void addObject(PObject*);
        void removeObject(PObject*);

    private:
        std::list<PObject*> m_objects ;
        glm::vec3 m_gravity ;
        void integrate(float step);
        void broadPhase();
        void narrowPhase();
        std::list<std::array<PObject*,2>> m_potentialCollisions ;
        

};

#endif
