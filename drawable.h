#ifndef Drawable_H
#define Drawable_H

#define GET_ADDRESS(base, offset) ((char*)(base) + (offset))

#ifdef __LINUX__
    #include <unistd.h>
#endif

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <iostream>
#include "shader.h"

class Drawable
{
    public:
        Drawable() ;
        virtual ~Drawable();

        void setShader(Shader* shader);
        void setModel(glm::mat4 model) ;

        const Shader* getShader() const;
        const glm::mat4& getModel() const;
        GLuint getIdVAO() const;
        GLuint getIdVBO() const;
        GLuint getIdIndices() const;
        int getIndicesNumber() const;

        void rotate(glm::vec3 axis, float angle);
        void translate(glm::vec3 translation);
        void homothetie(glm::vec3 homoth) ;

		void load(std::vector<glm::vec3> const &vertices, std::vector<glm::uvec3> const &indices);
        void update(const std::vector<float> &data, int offset);


    protected:

        GLuint m_idVAO;
        GLuint m_idVBO;
        GLuint m_idIndices;

        Shader* m_shader;
        int m_indicesNumber;
        glm::mat4 m_model;

};

#endif
