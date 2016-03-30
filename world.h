#ifndef WORLD_H
#define WORLD_H

#include "physic/pworld.h"
#include "graphics/gworld.h"
#include "object.h" 

class World
{
    public:
        World();
        ~World();

        PWorld& getPWorld();
        GWorld& getGWorld();

        void addObject(const Object& obj);
        void translateObject(Object& obj, glm::vec3 t);
        void rotateObject(Object& obj, glm::vec3 r);

    private:
        PWorld m_pworld;
        GWorld m_gworld;
};

#endif
