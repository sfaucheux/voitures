#ifndef POINTCONTACT_H
#define POINTCONTACT_H

#include "contact.h"

class PointContact : public Contact
{
    public:
        PointContact(glm::vec3 point, glm::vec3 normal);
        virtual ~PointContact();

        virtual glm::vec3 solveImpulse(PObject* p1, PObject* p2) ; 
        virtual glm::vec3 solvePosition(PObject* p1, PObject* p2) ;
        virtual void inverse();

    //private:
        glm::vec3 m_point;
        glm::vec3 m_normal;
};

#endif
