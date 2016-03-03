#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include <tuple>
#include "../glm/glm.hpp"

#include "sphere.h"
#include "box.h"
#include "mesh.h"

float square(float f);

namespace Collision
{
bool collide(const Sphere* obj1, const Sphere* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj1, const Sphere* obj2);

bool collide(const Sphere* obj1, const Box* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj1, const Box* obj2);

bool collide(const Sphere* obj1, const Mesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj1, const Mesh* obj2);

bool collide(const Box* obj1, const Box* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj1, const Box* obj2);

bool collide(const Box* obj1, const Mesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj1, const Mesh* obj2);

bool collide(const Mesh* obj1, const Mesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj1, const Mesh* obj2);
}

#endif
