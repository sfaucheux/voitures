#ifndef Sphere_H
#define Sphere_H

#include "geometry.h"

class Box;
class Mesh;

class Sphere : public Geometry 
{
    public:
        Sphere(float radius);

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Box* obj) const;
        bool collide(const Mesh* obj) const;
        bool collide(const Sphere* obj) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj) const;

        float getRadius() const;


    private:
        float m_radius;

};

#endif
