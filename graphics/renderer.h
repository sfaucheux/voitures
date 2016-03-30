#ifndef Renderer_H
#define Renderer_H

#include "../glm/glm.hpp"

#include "camera.h"
#include "drawable.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        Camera& getCamera();
        void setProjection(glm::mat4& projection);
        void setPerspective(float fov, float ratio, float near, float far);
        void setDefaultShader(Shader* shader);
        void draw(Drawable const& drawable, GLenum mode = GL_FILL) const;


    private:
        glm::mat4 m_projection ;
        Camera m_camera ;
        Shader* m_defaultShader;

};

#endif
