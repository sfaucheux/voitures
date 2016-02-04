#include <iostream>

#include "../glm/gtx/transform.hpp"

#include "drawable.h"

#define GET_ADDRESS(base, offset) ((char*)(base) + (offset))

using namespace std;

Drawable::Drawable() : m_idVAO(0), m_idVBO(0), m_idIBO(0), m_idTBO(0), m_shader(nullptr), m_model(1.0)
{
}

Drawable::~Drawable()
{
    glDeleteBuffers(1, &m_idVBO);
    glDeleteVertexArrays(1, &m_idVAO);
}

void Drawable::setShader(Shader* shader)
{
    m_shader = shader;
}
void Drawable::setTexture(Texture* texture)
{
    m_texture = texture;
}

void Drawable::setModel(glm::mat4 model)
{
    m_model = model;
}

const Shader* Drawable::getShader() const
{
    return m_shader;
}
const Texture* Drawable::getTexture() const
{
    return m_texture;
}

const glm::mat4& Drawable::getModel() const
{
    return m_model;
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

void Drawable::rotate(glm::vec3 axis, float angle)
{
    m_model = glm::rotate(m_model, angle, axis);
}

void Drawable::translate(glm::vec3 translation)
{
    m_model = glm::translate(m_model, translation);
}

void Drawable::homothetie(glm::vec3 homoth)
{
    m_model = glm::scale(m_model, homoth);
}

//void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<unsigned int> const &indices, std::vector<glm::vec2> const &textures)
void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices, std::vector<glm::vec2> const &textures)
{
    int sizeVertices = sizeof(glm::vec3) * vertices.size();
    //int sizeIBO = sizeof(unsigned int) * indices.size();
    int sizeIBO = sizeof(glm::vec3) * indices.size();
    int sizeTBO = sizeof(glm::vec2) * textures.size();


    //VAO
    if (glIsVertexArray(m_idVAO) == GL_TRUE)
        glDeleteVertexArrays(1, &m_idVAO);
    
    //Création et activation.
    glGenVertexArrays(1, &m_idVAO);
    glBindVertexArray(m_idVAO);

    //VBO Vertices.
    if (glIsBuffer(m_idVBO) == GL_TRUE)
      glDeleteBuffers(1, &m_idVBO);
    
    //Création et activation.
    glGenBuffers(1, &m_idVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
    //Allocation.
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, &vertices[0], GL_STATIC_DRAW);
    //Identifiacation.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    //VBO Indices
    if (glIsBuffer(m_idIBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idIBO);
    
    //Création et activation
    glGenBuffers(1, &m_idIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIBO);
    //Allocation
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIBO, &indices[0], GL_STATIC_DRAW);
    
    //VBO Textures
    if (glIsBuffer(m_idTBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idTBO) ;
    
    //Création et activation.
    glGenBuffers(1, &m_idTBO);
    glBindBufferARB(GL_ARRAY_BUFFER, m_idTBO) ;
    //Allocation
    glBufferData(GL_ARRAY_BUFFER, sizeTBO, &textures[0], GL_STATIC_DRAW);
    //Identification.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //a activer quand on pourra charger des textures.
    //glBindTexture(GL_TEXTURE_2D, drawable.getTexture()->getId());

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
