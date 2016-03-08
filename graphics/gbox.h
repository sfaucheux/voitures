#ifndef gBox_H
#define gBox_H

#include "drawable.h"
#include "../geometry/box.h"

class gBox : public Drawable
{
    public:
        gBox(Box& b);
        virtual ~gBox();

};

#endif
