#ifndef Renderer_H
#define Renderer_H

#include <GL/glew.h>
#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "drawable.h"
#include "camera.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        Camera& getCamera();
        void setProjection(glm::mat4& projection);
        void setPerspective(float fov, float ratio, float near, float far);
        void draw(Drawable const& objet);


    private:
        glm::mat4 m_projection ;
        Camera m_camera ;

};

#endif
