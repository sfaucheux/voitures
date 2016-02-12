#ifndef PSphere_H
#define PSphere_H

#include "pobject.h"

class PSphere : public PObject
{
    public:
        PSphere(float radius) ;

        virtual int collide(PObject* obj) ;
        virtual int collideWithBox(PBox* obj) ;
        virtual int collideWithMesh(PMesh* obj) ;
        virtual int collideWithSphere(PSphere* obj) ;

        float getRadius() const;


    private:
        float m_radius;

};

#endif
