#ifndef Renderer_H
#define Renderer_H

#include "glm/glm.hpp"

#include "camera.h"
#include "object.h"
#include "drawable.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        Camera& getCamera();
        void setProjection(glm::mat4& projection);
        void setPerspective(float fov, float ratio, float near, float far);
        void draw(Object const& object, GLenum mode = GL_FILL);
        void draw(Drawable const& drawable, GLenum mode = GL_FILL);


    private:
        glm::mat4 m_projection ;
        Camera m_camera ;

};

#endif
