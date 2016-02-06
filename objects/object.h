#ifndef Object_H
#define Object_H

#include <string>

#include "../glm/glm.hpp"

#include "../graphics/shader.h"
#include "../graphics/drawable.h"
#include "../physic/pobject.h"

class Object
{
    public:
        enum ObjectType {
            Box,
            Sphere,
            Mesh
        };

        Object();
        virtual ~Object();

        void setShader(Shader* shader);
        void setTexture(Texture* tex);

        virtual ObjectType getType() = 0;
        PObject* getPObject();
        Drawable const& getDrawable() const;
        const Shader* getShader() const;

        void sync();
        void translate(glm::vec3 t);
        void rotate(glm::vec3 r);


    protected:
		Drawable m_gObj;
		PObject* m_pObj;

};

#endif
