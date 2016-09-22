#ifndef CONTACT_H
#define CONTACT_H

#include "../physic/pobject.h"

class Contact 
{
    public:
        Contact();
        virtual ~Contact();
        virtual void solveImpulse(PObject* obj1, PObject* obj2) = 0; 
        virtual void solvePosition(PObject* obj1, PObject* obj2, glm::vec3* t1, glm::vec3* t2, glm::vec3* r1, glm::vec3* r2) = 0;

        virtual void inverse();
        
    private:

};

#endif
