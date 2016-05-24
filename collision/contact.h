#ifndef CONTACT_H
#define CONTACT_H

#include "../physic/pobject.h"

class Contact 
{
    public:
        Contact();
        virtual ~Contact();
        virtual glm::vec3 solveImpulse(PObject* p1, PObject* p2) = 0; 
        virtual glm::vec3 solvePosition(PObject* p1, PObject* p2) = 0;

        virtual void inverse();
        
    private:

};

#endif
