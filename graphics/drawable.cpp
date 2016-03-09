#include <iostream>

#include "../glm/gtx/transform.hpp"

#include "drawable.h"

#define GET_ADDRESS(base, offset) ((char*)(base) + (offset))

using namespace std;

Drawable::Drawable(Geometry& geom) : m_idVAO(0), m_idVBO(0), m_idIBO(0), m_shader(nullptr), m_texture(nullptr), m_geometry(geom)
{
}

Drawable::~Drawable()
{
    if (glIsBuffer(m_idVBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idVBO);
    if (glIsVertexArray(m_idVAO) == GL_TRUE)
        glDeleteVertexArrays(1, &m_idVAO);
    if (glIsBuffer(m_idIBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idIBO);
}

void Drawable::setShader(Shader* shader)
{
    m_shader = shader;
}

void Drawable::setTexture(Texture* texture)
{
    m_texture = texture;
}

const Shader* Drawable::getShader() const
{
    return m_shader;
}

const Texture* Drawable::getTexture() const
{
    return m_texture;
}

GLuint Drawable::getIdVAO() const
{
    return m_idVAO;
}

GLuint Drawable::getIdVBO() const
{
    return m_idVBO;
}

GLuint Drawable::getIdIBO() const
{
    return m_idIBO;
}

int Drawable::getVerticesNumber() const
{
    return m_verticesNumber;
}

int Drawable::getIndicesNumber() const
{
    return m_indicesNumber;
}

const Geometry& Drawable::getGeometry() const
{
    return m_geometry;
}

void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices, std::vector<glm::vec2> const *textures)
{
    loadVerticesVBO(vertices);
    loadIndicesVBO(indices);
    if (textures)
        loadTexturesVBO(textures);
    loadVAO(textures);
}

void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<unsigned int> const &indices, std::vector<glm::vec2> const *textures)
{
    loadVerticesVBO(vertices);
    loadIndicesVBO(indices);
    if (textures)
        loadTexturesVBO(textures);
    loadVAO(textures);
}

void Drawable::loadVAO(bool withTextures)
{
    if (glIsVertexArray(m_idVAO) == GL_TRUE)
        glDeleteVertexArrays(1, &m_idVAO);
    
    //Création et activation.
    glGenVertexArrays(1, &m_idVAO);
    glBindVertexArray(m_idVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
    //Identification.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    if (withTextures)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_idTBO);
        //Identification.
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIBO);
    glBindVertexArray(0);
}

void Drawable::loadVerticesVBO(std::vector<glm::vec3> const &vertices)
{
    int sizeVertices = sizeof(glm::vec3) * vertices.size();
    if (glIsBuffer(m_idVBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idVBO);

    //Création et activation.
    glGenBuffers(1, &m_idVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
    //Allocation.
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_verticesNumber = vertices.size() * 3;
}

void Drawable::loadIndicesVBO(std::vector<glm::uvec3> const &indices)
{
    int sizeIBO = sizeof(glm::uvec3) * indices.size();
    if (glIsBuffer(m_idIBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idIBO);

    //Création et activation
    glGenBuffers(1, &m_idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIBO);
    //Allocation
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIBO, &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    m_indicesNumber = indices.size() * 3;
}

void Drawable::loadIndicesVBO(std::vector<unsigned int> const &indices)
{
    int sizeIBO = sizeof(unsigned int) * indices.size();
    if (glIsBuffer(m_idIBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idIBO);

    //Création et activation
    glGenBuffers(1, &m_idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIBO);
    //Allocation
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIBO, &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    m_indicesNumber = indices.size();
}

void Drawable::loadTexturesVBO(std::vector<glm::vec2> const *textures)
{
    int sizeTBO = sizeof(glm::vec2) * textures->size();
    if (glIsBuffer(m_idTBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idTBO);

    //Création et activation.
    glGenBuffers(1, &m_idTBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_idTBO);
    //Allocation
    glBufferData(GL_ARRAY_BUFFER, sizeTBO, &(*textures)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
