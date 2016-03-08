#ifndef Sphere_H
#define Sphere_H

#include "geometry.h"

class Box;
class Mesh;

class Sphere : public Geometry 
{
    public:
        Sphere(float radius);
        virtual ~Sphere();

        float getRadius() const;


        virtual bool collide(const Geometry* obj) const;
        virtual bool collideWithSphere(const Sphere* obj) const;
        virtual bool collideWithBox(const Box* obj) const;
        virtual bool collideWithMesh(const Mesh* obj) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithSphere(const Sphere* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithBox(const Box* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithMesh(const Mesh* obj) const;

    private:
        float m_radius;

};

#endif
