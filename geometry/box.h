#ifndef Box_H
#define Box_H

#include "geometry.h"

class Sphere;
class Mesh;

class Box : public Geometry 
{
    public:
        Box(float width, float height, float depth);
        virtual ~Box();

        float getHeight() const;
        float getWidth() const;
        float getDepth() const;


        virtual bool collide(const Geometry* obj) const;
        virtual bool collideWithSphere(const Sphere* obj) const;
        virtual bool collideWithBox(const Box* obj) const;
        virtual bool collideWithMesh(const Mesh* obj) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithSphere(const Sphere* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithBox(const Box* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithMesh(const Mesh* obj) const;
        
    private:
        float m_width;
        float m_height;
        float m_depth;

};

#endif
