#ifndef WORLD_H
#define WORLD_H

#include "physic/pworld.h"
#include "object.h" 

class World
{
    public:
        World();
        ~World();

        PWorld& getPWorld();

        void addObject(const Object& obj);
        void translateObject(Object& obj, glm::vec3 t);
        void rotateObject(Object& obj, glm::vec3 r);

    private:
        PWorld m_pworld ;
};

#endif
