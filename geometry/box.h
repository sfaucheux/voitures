#ifndef Box_H
#define Box_H

#include "geometry.h"

#include "../glm/glm.hpp"
#include <array>

class Sphere;
class Mesh;

class Box : public Geometry 
{
    public:
        Box(float width, float height, float depth);
        Box(glm::vec3 size);
        virtual ~Box();

        float getHeight() const;
        float getWidth() const;
        float getDepth() const;
        glm::vec3 getSize() const;

        std::array<glm::vec3,8> getVertices() const;
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
        glm::vec3 m_size;

};

#endif
