#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include <tuple>
#include "../glm/glm.hpp"

#include "psphere.h"
#include "pbox.h"
#include "pmesh.h"

float square(float f);


bool collideSphereWithSphere(PSphere* obj1, PSphere* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsSphereWithSphere(PSphere* obj1, PSphere* obj2);

bool collideSphereWithBox(PSphere* obj1, PBox* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsSphereWithBox(PSphere* obj1, PBox* obj2);

bool collideSphereWithMesh(PSphere* obj1, PMesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsSphereWithMesh(PSphere* obj1, PMesh* obj2);

bool collideBoxWithBox(PBox* obj1, PBox* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsBoxWithBox(PBox* obj1, PBox* obj2);

bool collideBoxWithMesh(PBox* obj1, PMesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsBoxWithMesh(PBox* obj1, PMesh* obj2);

bool collideMeshWithMesh(PMesh* obj1, PMesh* obj2);
std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsMeshWithMesh(PMesh* obj1, PMesh* obj2);

#endif
