#ifndef Box_H
#define Box_H

#include "object.h"

class Box : public Object
{
    public:
        Box(float width, float height, float depth);
        virtual ~Box();

        ObjectType getType();


    private:

};

#endif
