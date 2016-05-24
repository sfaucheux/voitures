#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include <tuple>
#include "../glm/glm.hpp"

#include "sphere.h"
#include "box.h"
#include "mesh.h"

namespace Collisions
{
    enum ContactType{PLANE, EDGE, POINT};
    bool collide(const Sphere* obj1, const Sphere* obj2);
    Contact* collisionPoints(const Sphere* obj1, const Sphere* obj2);
    bool collide(const Sphere* s, const Box* b);
    bool collide(const Box* b, const Sphere* s);
    Contact* collisionPoints(const Sphere* s, const Box* b);
    Contact* collisionPoints(const Box* b, const Sphere* s);
    bool collide(const Sphere* s, const Mesh* m);
    bool collide(const Mesh* m, const Sphere* s);
    Contact* collisionPoints(const Sphere* s, const Mesh* m);
    Contact* collisionPoints(const Mesh* m, const Sphere* s);
    bool collide(const Box* obj1, const Box* obj2);
    Contact* collisionPoints(const Box* obj1, const Box* obj2);
    bool collide(const Box* b, const Mesh* m);
    bool collide(const Mesh* m, const Box* b);
    Contact* collisionPoints(const Box* b, const Mesh* m);
    Contact* collisionPoints(const Mesh* m, const Box* b);
    bool collide(const Mesh* obj1, const Mesh* obj2);
    Contact* collisionPoints(const Mesh* obj1, const Mesh* obj2);
}

#endif
