#include "pobject.h"

class PSphere : public PObject
{
    public:
        PSphere(float radius);

        virtual bool collide(PObject* obj);
        virtual bool collideWithBox(PBox* obj);
        virtual bool collideWithMesh(PMesh* obj);
        virtual bool collideWithSphere(PSphere* obj);

        virtual std::vector<glm::vec3> collisionPoints(PObject* obj);
        virtual std::vector<glm::vec3> collisionPointsWithBox(PBox* obj);
        virtual std::vector<glm::vec3> collisionPointsWithMesh(PMesh* obj);
        virtual std::vector<glm::vec3> collisionPointsWithSphere(PSphere* obj);

        float getRadius() const;


    private:
        float m_radius;

};
