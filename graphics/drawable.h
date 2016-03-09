#ifndef Drawable_H
#define Drawable_H

#include <cstring>
#include <vector>

#include "../glm/glm.hpp"

#include "../geometry/geometry.h"
#include "shader.h"
#include "texture.h"

class Drawable
{
    public:
        Drawable(Geometry& geom);
        virtual ~Drawable();

        void setShader(Shader* shader);
        void setTexture(Texture* texture);

        const Shader* getShader() const;
        const Texture* getTexture() const;
        GLuint getIdVAO() const;
        GLuint getIdVBO() const;
        GLuint getIdIBO() const;
        int getIndicesNumber() const;
        int getVerticesNumber() const;
        const Geometry& getGeometry() const;

        void load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices, std::vector<glm::vec2> const *textures = nullptr);
        void load(std::vector<glm::vec3> const &vertices, std::vector<unsigned int> const &indices, std::vector<glm::vec2> const *textures = nullptr);


    protected:
        GLuint m_idVAO;
        GLuint m_idVBO;
        GLuint m_idIBO;
        GLuint m_idTBO;

        Shader* m_shader;
        Texture* m_texture;

        int m_indicesNumber;
        int m_verticesNumber;

        Geometry& m_geometry;


    private:
        void loadVAO(bool withTextures);
        void loadVerticesVBO(std::vector<glm::vec3> const &vertices);
        void loadIndicesVBO(std::vector<glm::uvec3> const &indices);
        void loadIndicesVBO(std::vector<unsigned int> const &indices);
        void loadTexturesVBO(std::vector<glm::vec2> const *textures);

};

#endif
