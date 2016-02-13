#ifndef Sphere_H
#define Sphere_H

#include "object.h"

class Sphere : public Object
{
    public:
        Sphere(float radius);
        virtual ~Sphere();

        ObjectType getType();


    private:

};

#endif
