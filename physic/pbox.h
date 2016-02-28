#ifndef PBox_H
#define PBox_H

#include "pobject.h"

class PBox : public PObject
{
    public:
        PBox(float width, float height, float depth, Coordinates& coord);

        virtual bool collide(PObject* obj);
        virtual bool collideWithBox(PBox* obj);
        virtual bool collideWithMesh(PMesh* obj);
        virtual bool collideWithSphere(PSphere* obj);

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(PObject* obj);
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithBox(PBox* obj);
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithMesh(PMesh* obj);
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithSphere(PSphere* obj);


    private:
        float m_width;
        float m_height;
        float m_depth;

};

#endif
