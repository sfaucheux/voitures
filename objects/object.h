#ifndef Object_H
#define Object_H

#include <string>

#include "../glm/glm.hpp"

#include "../graphics/shader.h"
#include "../graphics/drawable.h"
#include "../physic/pobject.h"

#include "../geometry/sphere.h"
#include "../geometry/box.h"
#include "../geometry/mesh.h"

class Object
{
    public:
        Object(Sphere s);
        Object(Box b);
        Object(Mesh m);
        virtual ~Object();

        void setShader(Shader* shader);

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
