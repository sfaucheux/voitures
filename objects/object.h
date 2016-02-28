#ifndef Object_H
#define Object_H

#include <string>

#include "../glm/glm.hpp"

#include "coordinates.h"
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

        virtual ObjectType getType() = 0;
        PObject* getPObject() const;
        Drawable* getDrawable() const;
        Coordinates& getCoordinates();


    protected:
        Coordinates m_coord;
		Drawable* m_gObj;
		PObject* m_pObj;

};

#endif
