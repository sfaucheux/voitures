#ifndef Drawable_H
#define Drawable_H

#include <cstring>
#include <vector>

#include "../glm/glm.hpp"

#include "shader.h"
#include "../objects/coordinates.h"

class Drawable
{
    public:
        Drawable(Coordinates* coord);
        virtual ~Drawable();

        void setShader(Shader* shader);

        const Shader* getShader() const;
        Coordinates* getCoordinates() const;
        GLuint getIdVAO() const;
        GLuint getIdVBO() const;
        GLuint getIdIBO() const;
        int getIndicesNumber() const;
        int getVerticesNumber() const;

        void load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices);
        void update(const std::vector<float> &data, int offset);


    protected:

        GLuint m_idVAO;
        GLuint m_idVBO;
        GLuint m_idIBO;

        Shader* m_shader;
        int m_indicesNumber;
        int m_verticesNumber;
        Coordinates* m_coord;

};

#endif
