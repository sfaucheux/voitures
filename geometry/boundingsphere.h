#ifndef BOUNDING_SPHERE
#define BOUNDING_SPHERE

#include "../glm/glm.hpp"

class BoundingSphere
{
    public:
        BoundingSphere(float radius, glm::vec3 position = glm::vec3(0));
        float getRadius() const ;
        glm::vec3 getPosition() const ;

        bool collide(const BoundingSphere &s) const;

        void setPosition(glm::vec3 pos) ;
    private:
        float m_radius ;
        glm::vec3 m_position ;

};

#endif
