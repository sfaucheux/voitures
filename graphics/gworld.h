#ifndef GWORLD_H
#define GWORLD_H

#include <list>
#include "drawable.h"
#include "renderer.h"
#include "../glm/glm.hpp"

class GWorld
{
    public:
        GWorld();
        ~GWorld();
        void addObject(Drawable* obj);
        void translateObject(Drawable* obj, glm::vec3 t);
        void draw(const Renderer& rdr, GLenum mode = GL_FILL);

    private:
        std::vector<Drawable*> m_objects ;
};

#endif
