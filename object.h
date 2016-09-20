#ifndef Object_H
#define Object_H

#include <string>

#include "glm/glm.hpp"

#include "graphics/shader.h"
#include "graphics/drawable.h"
#include "physic/pobject.h"
#include "physic/pworld.h"

#include "geometry/sphere.h"
#include "geometry/box.h"
#include "geometry/mesh.h"

class Object
{
    public:
        Object(Sphere s);
        Object(Box b);
        Object(Mesh m);
        virtual ~Object();

        PObject* getPObject() const;
        Drawable* getDrawable() const;
        const Geometry* getGeometry() const;

        void translate(glm::vec3 t, PWorld* pworld = nullptr);
        void rotate(glm::vec3 r);


    protected:
        Geometry* m_geom;
	Drawable* m_gObj;
	PObject* m_pObj;

};

#endif
