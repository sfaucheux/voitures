#include "pobject.h"

class PMesh : public PObject
{
    public:
        PMesh();
        bool collide(PObject* obj);
        bool collideWithSphere(PSphere *s);
        bool collideWithBox(PBox* b);
        bool collideWithMesh(PMesh* b);

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(PObject* obj);
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithBox(PBox* obj) ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithMesh(PMesh* obj) ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithSphere(PSphere* obj) ;
    private:
};
