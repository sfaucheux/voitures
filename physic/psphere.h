#include "pobject.h"

class PSphere : public PObject
{
    public:
        PSphere(float radius) ;

        virtual bool collide(PObject* obj) ;
        virtual bool collideWithBox(PBox* obj) ;
        virtual bool collideWithMesh(PMesh* obj) ;
        virtual bool collideWithSphere(PSphere* obj) ;

        float getRadius() const;
    private:
        float m_radius;
};
