#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../glm/glm.hpp"
#include "vector"
#include "tuple"

class Geometry
{
    public:
        virtual bool collide(const Geometry* obj) const = 0 ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const = 0 ;
};

#endif
