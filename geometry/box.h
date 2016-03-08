#ifndef Box_H
#define Box_H

#include "geometry.h"

class Sphere;
class Mesh;

class Box : public Geometry 
{
    public:
        Box(float width, float height, float depth);

        float getHeight() const;
        float getWidth() const;
        float getDepth() const;

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Sphere* s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* m) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m) const;


    private:
        float m_width;
        float m_height;
        float m_depth;

};

#endif
