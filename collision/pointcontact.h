#ifndef POINTCONTACT_H
#define POINTCONTACT_H

#include "contact.h"
#include "../glm/glm.hpp"

class PointContact : public Contact
{
    public:
        PointContact(glm::vec3 point, glm::vec3 normal, float overlap);
        virtual ~PointContact();

        virtual void solveImpulse(PObject* obj1, PObject* obj2) ; 
        virtual void solvePosition(PObject* obj1, PObject* obj2, glm::vec3* t1, glm::vec3* t2, glm::vec3* r1, glm::vec3* r2);
        virtual void init(PObject* obj1, PObject* obj2);
        virtual void inverse();

    private:
        glm::vec3 m_point;
        glm::vec3 m_normal;
        float m_overlap;
        
        float m_e, m_m1, m_m2, m_m1inv, m_m2inv, m_jr, m_js, m_jd;
        glm::vec3 m_r1, m_r2, m_moment1, m_moment2, m_t;
};

#endif
