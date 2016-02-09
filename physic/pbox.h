#include "pobject.h"

class PBox : public PObject
{
    public:
        PBox(float width, float height, float depth);

        virtual int collide(PObject* obj)  ;
        virtual int collideWithBox(PBox* obj)  ;
        virtual int collideWithMesh(PMesh* obj) ;
        virtual int collideWithSphere(PSphere* obj) ;
    private:
        float m_width;
        float m_height;
        float m_depth;
};
