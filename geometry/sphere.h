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
        bool collide(const Sphere* s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* m) const;

        virtual Contact* collisionPoints(const Geometry* obj) const;
        Contact* collisionPoints(const Sphere* s) const;
        Contact* collisionPoints(const Box* b) const;
        Contact* collisionPoints(const Mesh* m) const;

        virtual AABB getAABB() const;
        virtual BoundingSphere getBoundingSphere() const;

    private:
        float m_radius;

};

#endif
