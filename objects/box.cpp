#include "../glm/glm.hpp"

#include "box.h"
#include "../physic/pbox.h"

using namespace glm;

Box::Box(float w, float h, float d)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    vertices.push_back(vec3( w / 2, -h / 2, -d / 2));
    vertices.push_back(vec3( w / 2, -h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2, -h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2, -h / 2, -d / 2));
    vertices.push_back(vec3( w / 2,  h / 2, -d / 2));
    vertices.push_back(vec3( w / 2,  h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2,  h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2,  h / 2, -d / 2));

    indices.push_back(uvec3(0, 1, 2));
    indices.push_back(uvec3(0, 2, 3));
    indices.push_back(uvec3(4, 7, 6));
    indices.push_back(uvec3(4, 6, 5));
    indices.push_back(uvec3(0, 4, 5));
    indices.push_back(uvec3(0, 5, 1));
    indices.push_back(uvec3(1, 5, 6));
    indices.push_back(uvec3(1, 6, 2));
    indices.push_back(uvec3(2, 6, 7));
    indices.push_back(uvec3(2, 7, 3));
    indices.push_back(uvec3(4, 0, 3));
    indices.push_back(uvec3(4, 3, 7));

    m_gObj = new Drawable(&m_coord);
    m_gObj->load(vertices, indices);
    m_pObj = new PBox(w, h, d, m_coord);
}

Box::~Box()
{
    delete m_pObj;
    delete m_gObj;
}

Object::ObjectType Box::getType()
{
    return Object::Box;
}
