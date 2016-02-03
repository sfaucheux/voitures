#include "drawable.h"

Drawable::Drawable() : m_idVAO(0), m_idVBO(0), m_shader(nullptr), m_model(1.0)
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

void Drawable::setModel(glm::mat4 model)
{
    m_model = model;
}

const Shader* Drawable::getShader() const
{
    return m_shader;
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

GLuint Drawable::getIdIndices() const
{
    return m_idIndices;
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

void Drawable::load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices)
{
    int sizeVertices = 3 * sizeof(float) * vertices.size();
    int sizeIndices = 3 * sizeof(unsigned int) * indices.size();

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

    if (glIsBuffer(m_idIndices) == GL_TRUE)
        glDeleteBuffers(1, &m_idIndices);

    glGenBuffers(1, &m_idIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, &indices[0], GL_STATIC_DRAW);

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
