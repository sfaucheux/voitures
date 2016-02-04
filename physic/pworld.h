#ifndef PWorld_H
#define PWorld_H

#include <list>

#include "../glm/glm.hpp"

#include "pobject.h"

class PWorld 
{
    public:
        PWorld();
        void setGravity(glm::vec3 gravity);
        void update();
        void addObject(PObject*);
        void removeObject(PObject*);


    private:
        std::list<PObject*> m_objects ;
        glm::vec3 m_gravity ;

};

#endif
