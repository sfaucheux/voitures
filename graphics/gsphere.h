#ifndef gSphere_H
#define gSphere_H

#include "drawable.h"
#include "../geometry/sphere.h"

class gSphere : public Drawable
{
    public:
        gSphere(Sphere& s);
        virtual ~gSphere();

};

#endif
