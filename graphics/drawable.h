#ifndef Drawable_H
#define Drawable_H

#include <cstring>
#include <vector>

#include "../glm/glm.hpp"

#include "shader.h"
#include "texture.h"

class Drawable
{
    public:
        Drawable() ;
        virtual ~Drawable();

        void setShader(Shader* shader);
        void setTexture(Texture* texture);
        void setModel(glm::mat4 model) ;

        const Shader* getShader() const;
        const Texture* getTexture() const;
        const glm::mat4& getModel() const;
        GLuint getIdVAO() const;
        GLuint getIdVBO() const;
        GLuint getIdIBO() const;
        int getIndicesNumber() const;
        int getVerticesNumber() const;

        void rotate(glm::vec3 axis, float angle);
        void translate(glm::vec3 translation);
        void homothetie(glm::vec3 homoth) ;

        void load(std::vector<glm::vec3> const &vertices, std::vector<unsigned int> const &indices, std::vector<glm::vec2> const &textures = std::vector<glm::vec2>());
        //void load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices, std::vector<glm::vec2> const &textures = std::vector<glm::vec2>());
        void update(const std::vector<float> &data, int offset);


    protected:

        GLuint m_idVAO;
        GLuint m_idVBO;
        GLuint m_idIBO;
        GLuint m_idTBO;

        Shader* m_shader;
        Texture* m_texture;
        int m_indicesNumber;
        int m_verticesNumber;
        glm::mat4 m_model;

};

#endif
