#include "renderer.h"

Renderer::Renderer() : m_projection(1.0), m_camera(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1))
{
}

Renderer::~Renderer()
{
}

void Renderer::setProjection(glm::mat4 &projection)
{
    m_projection = glm::mat4(projection) ;
}

void Renderer::setPerspective(float angle, float ratio, float near, float far)
{
    m_projection = glm::perspective(angle, ratio, near, far);
}

void Renderer::draw(Drawable const& objet, GLenum mode)
{
    GLuint shader = objet.getShader()->getProgramID() ;
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glUseProgram(shader);
        glBindVertexArray(objet.getIdVAO());
                glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
                glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(m_camera.getView()));
                glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(objet.getModel()));
                //a activer quand on pourra charger des textures.
                //glBindTexture(GL_TEXTURE_2D, objet.getTexture()->getId());
                glDrawElements(GL_TRIANGLES, objet.getIndicesNumber(), GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    glUseProgram(0);
}

Camera& Renderer::getCamera()
{
	return m_camera;
}
