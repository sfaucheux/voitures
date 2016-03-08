#ifndef Drawable_H
#define Drawable_H

#include <cstring>
#include <vector>

#include "../glm/glm.hpp"

#include "../geometry/geometry.h"
#include "shader.h"

class Drawable
{
    public:
        Drawable(Geometry& geom);
        virtual ~Drawable();

        void setShader(Shader* shader);

        const Shader* getShader() const;
        GLuint getIdVAO() const;
        GLuint getIdVBO() const;
        GLuint getIdIBO() const;
        int getIndicesNumber() const;
        int getVerticesNumber() const;
        const Geometry& getGeometry() const;

        void load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices);

    protected:

        GLuint m_idVAO;
        GLuint m_idVBO;
        GLuint m_idIBO;

        Shader* m_shader;

        int m_indicesNumber;
        int m_verticesNumber;

        Geometry& m_geometry;
};

#endif
