#include "pobject.h"

class PMesh : public PObject
{
    public:
        PMesh();

        bool collide(PObject* obj);
        bool collideWithSphere(PSphere *s);
        bool collideWithBox(PBox* b);
        bool collideWithMesh(PMesh* b);


    private:

};
