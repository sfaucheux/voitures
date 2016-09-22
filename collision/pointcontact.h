#ifndef POINTCONTACT_H
#define POINTCONTACT_H

#include "contact.h"

class PointContact : public Contact
{
    public:
        PointContact(glm::vec3 point, glm::vec3 normal, float overlap);
        virtual ~PointContact();

        virtual void solveImpulse(PObject* obj1, PObject* obj2) ; 
        virtual void solvePosition(PObject* obj1, PObject* obj2, glm::vec3* t1, glm::vec3* t2, glm::vec3* r1, glm::vec3* r2);
        virtual void inverse();

    private:
        glm::vec3 m_point;
        glm::vec3 m_normal;
        float m_overlap;

};

#endif
