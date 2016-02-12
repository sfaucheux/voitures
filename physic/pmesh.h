#ifndef PMesh_H
#define PMesh_H

#include "pobject.h"

class PMesh : public PObject
{
    public:
        PMesh();
        int collide(PObject* obj);
        int collideWithSphere(PSphere *s);
        int collideWithBox(PBox* b);
        int collideWithMesh(PMesh* b);


    private:

};

#endif
