#include <vector>
#include "../glm/glm.hpp"
#include "gbox.h"

gBox::gBox(Box& b) : Drawable(b)
{
    float w = b.getWidth(), h = b.getHeight(), d = b.getDepth();
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    vertices.push_back(glm::vec3( w / 2, -h / 2, -d / 2));
    vertices.push_back(glm::vec3( w / 2, -h / 2,  d / 2));
    vertices.push_back(glm::vec3(-w / 2, -h / 2,  d / 2));
    vertices.push_back(glm::vec3(-w / 2, -h / 2, -d / 2));
    vertices.push_back(glm::vec3( w / 2,  h / 2, -d / 2));
    vertices.push_back(glm::vec3( w / 2,  h / 2,  d / 2));
    vertices.push_back(glm::vec3(-w / 2,  h / 2,  d / 2));
    vertices.push_back(glm::vec3(-w / 2,  h / 2, -d / 2));

    indices.push_back(glm::uvec3(0, 1, 2));
    indices.push_back(glm::uvec3(0, 2, 3));
    indices.push_back(glm::uvec3(4, 7, 6));
    indices.push_back(glm::uvec3(4, 6, 5));
    indices.push_back(glm::uvec3(0, 4, 5));
    indices.push_back(glm::uvec3(0, 5, 1));
    indices.push_back(glm::uvec3(1, 5, 6));
    indices.push_back(glm::uvec3(1, 6, 2));
    indices.push_back(glm::uvec3(2, 6, 7));
    indices.push_back(glm::uvec3(2, 7, 3));
    indices.push_back(glm::uvec3(4, 0, 3));
    indices.push_back(glm::uvec3(4, 3, 7));

    load(vertices, indices);
} 

gBox::~gBox()
{
}
