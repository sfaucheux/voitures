#ifndef Sphere_H
#define Sphere_H

#include "geometry.h"

class Box;
class Mesh;

class Sphere : public Geometry 
{
    public:
        Sphere(float radius);

        float getRadius() const;

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Sphere* s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* m) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m) const;


    private:
        float m_radius;

};

#endif
