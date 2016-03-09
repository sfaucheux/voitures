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
    bool collide(const Sphere* obj1, const Sphere* obj2);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj1, const Sphere* obj2);
    bool collide(const Sphere* s, const Box* b);
    bool collide(const Box* b, const Sphere* s);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s, const Box* b);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b, const Sphere* s);
    bool collide(const Sphere* s, const Mesh* m);
    bool collide(const Mesh* m, const Sphere* s);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s, const Mesh* m);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m, const Sphere* s);
    bool collide(const Box* obj1, const Box* obj2);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj1, const Box* obj2);
    bool collide(const Box* b, const Mesh* m);
    bool collide(const Mesh* m, const Box* b);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b, const Mesh* m);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m, const Box* b);
    bool collide(const Mesh* obj1, const Mesh* obj2);
    std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj1, const Mesh* obj2);
}

#endif
