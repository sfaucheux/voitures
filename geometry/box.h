#ifndef Box_H
#define Box_H

#include "geometry.h"

class Sphere;
class Mesh;

class Box : public Geometry 
{
    public:
        Box(float width, float height, float depth);

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Box* obj) const;
        bool collide(const Mesh* obj) const;
        bool collide(const Sphere* obj) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj) const;

        float getHeight() const;
        float getWidth() const;
        float getDepth() const;

    private:
        float m_width;
        float m_height;
        float m_depth;

};

#endif
