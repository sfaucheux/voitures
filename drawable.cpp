#include "drawable.h"

Drawable::Drawable() : m_idVAO(0) , m_idVBO(0), m_vertices(),m_couleurs(), m_textures(), /* m_shader(nullptr),*/ m_nomTexture (), m_model(1.0)
{
}

/*Drawable::Drawable(std::vector<float> textures, Shader* shader, std::string nomTexture) : m_idVAO(0), m_idVBO(0), m_vertices(std::vector<float>(0)),
m_couleurs(std::vector<float> (0)), m_textures(textures), m_shader(shader), m_nomTexture(nomTexture), m_model(1.0), m_verticesNumber(0)
{

}*/

Drawable::~Drawable()
{
    glDeleteBuffers(1, &m_idVBO);
    glDeleteVertexArrays(1, &m_idVAO);
}

/*void Affichable::Charger(std::vector<float> &vertices, std::vector<float> &couleurs)
{
    if(glIsBuffer(m_idVBO) == GL_TRUE)
        glDeleteBuffers(1, &m_idVBO);

    int tailleVertices = sizeof(float)*vertices.size();
    int tailleCouleurs = sizeof(float)*couleurs.size();

    glGenBuffers(1, &m_idVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
        glBufferData(GL_ARRAY_BUFFER, tailleCouleurs + tailleVertices, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, tailleVertices, &vertices[0]);
        glBufferSubData(GL_ARRAY_BUFFER, tailleVertices, tailleCouleurs, &couleurs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(glIsVertexArray(m_idVAO) == GL_TRUE)
        glDeleteVertexArrays(1, &m_idVAO);

    glGenVertexArrays(1, &m_idVAO);
    glBindVertexArray(m_idVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(float)));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_verticesNumber = vertices.size() / 3 ;
}
void Affichable::MiseAJour(const std::vector<float> &donnees, int decalage)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_idVBO);
        void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if(adresseVBO == NULL)
        {
            std::cerr << "Erreur au niveau de la récupération du VBO" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            return;
        }
        memcpy((char*)adresseVBO + decalage, &donnees[0], donnees.size()*sizeof(float));

        glUnmapBuffer(GL_ARRAY_BUFFER);
        adresseVBO = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Affichable::SetVertices(std::vector<float> vertices)
{
    m_vertices = vertices ;
    MiseAJour(m_vertices, 0);
}
void Affichable::SetCouleurs(std::vector<float> couleurs)
{
    m_couleurs = couleurs ;
    MiseAJour(m_vertices, m_vertices.size()*sizeof(float));
}
void Affichable::SetTextures(std::vector<float> textures)
{
    m_textures = textures ;
}
void Affichable::SetNomTexture(std::string nom)
{
    m_nomTexture = nom ;
}
void Affichable::SetShader(Shader *shader)
{
    m_shader = shader;
}
const std::vector<float>& Affichable::GetVertices() const
{
    return m_vertices ;
}
const std::vector<float>& Affichable::GetCouleurs() const
{
    return m_couleurs ;
}
const std::vector<float>& Affichable::GetTextures() const
{
    return m_textures ;
}
const glm::mat4& Affichable::GetModel() const
{
    return m_model ;
}
std::string Affichable::GetNomTexture() const
{
    return m_nomTexture;
}
const Shader* Affichable::GetShader() const
{
    return m_shader;
}
GLuint Affichable::GetIdVAO() const
{
    return m_idVAO;
}
GLuint Affichable::GetIdVBO() const
{
    return m_idVBO;
}
int Affichable::GetVerticesNumber() const
{
    return m_verticesNumber;
}
void Affichable::Tourner(glm::vec3 axe, float angle)
{
    m_model = glm::rotate(m_model,angle,axe);
}
void Affichable::Translater(glm::vec3 translation)
{
    m_model = glm::translate(m_model, translation);
}
void Affichable::Homothetie(glm::vec3 homothetie)
{
    m_model = glm::scale(m_model, homothetie);
}
void Affichable::SetModel(glm::mat4 model)
{
    m_model = model ;
}*/
