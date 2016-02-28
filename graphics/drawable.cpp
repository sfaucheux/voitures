#include <iostream>

#include "../glm/gtx/transform.hpp"

#include "drawable.h"

#define GET_ADDRESS(base, offset) ((char*)(base) + (offset))

using namespace std;

Drawable::Drawable(Coordinates* coord) : m_idVAO(0), m_idVBO(0), m_idIBO(0), m_shader(nullptr), m_coord(coord)
{
}

Drawable::~Drawable()
{
    glDeleteBuffers(1, &m_idVBO);
    glDeleteVertexArrays(1, &m_idVAO);
    glDeleteBuffers(1, &m_idIBO);
}

void Drawable::setShader(Shader* shader)
{
    m_shader = shader;
}

const Shader* Drawable::getShader() const
{
    return m_shader;
}

Coordinates* Drawable::getCoordinates() const
{
    return m_coord;
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

void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices)
{
    int sizeVertices = sizeof(glm::vec3) * vertices.size();
    int sizeIBO = sizeof(glm::uvec3) * indices.size();

    if (glIsVertexArray(m_idVAO) == GL_TRUE)
        glDeleteVertexArrays(1, &m_idVAO);

    glGenVertexArrays(1, &m_idVAO);
    glBindVertexArray(m_idVAO);

    if (glIsBuffer(m_idVBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idVBO);

    glGenBuffers(1, &m_idVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    if (glIsBuffer(m_idIBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idIBO);

    glGenBuffers(1, &m_idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIBO, &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_indicesNumber = indices.size() * 3 ;
    m_verticesNumber = vertices.size() * 3 ;

}

void Drawable::update(const std::vector<float> &data, int offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
        void* VBOAddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if (VBOAddress == NULL)
        {
            std::cerr << "Erreur au niveau de la récupération du VBO" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            return;
        }
        memcpy(GET_ADDRESS(VBOAddress, offset), &data[0], data.size() * sizeof(float));

        glUnmapBuffer(GL_ARRAY_BUFFER);
        VBOAddress = NULL;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
