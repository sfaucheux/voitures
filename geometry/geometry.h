#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../glm/glm.hpp"
#include "vector"
#include "tuple"
#include "boundingsphere.h"
#include "aabb.h"

class Box;
class Sphere;
class Mesh;

class Geometry
{
    public:
        Geometry();
        virtual ~Geometry();

        glm::vec3 getPosition() const;
        glm::vec3 getRotation() const;
        glm::mat4 const& getModel() const;
        glm::mat4 getRotationMatrix(glm::mat4 m = glm::mat4(1.0)) const;

        void translate(glm::vec3 translation);
        void rotate(glm::vec3 rotation);
        glm::vec3 getLocalPoint(const glm::vec3& point) const;
        glm::vec3 getWorldPoint(const glm::vec3& point) const;

        virtual bool collide(const Geometry* obj) const = 0 ;
        virtual bool collide(const Sphere* obj) const = 0 ;
        virtual bool collide(const Box* obj) const = 0 ;
        virtual bool collide(const Mesh* obj) const = 0 ;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const = 0 ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj) const = 0 ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj) const = 0 ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj) const = 0 ;

        virtual AABB getAABB() const = 0;
        virtual BoundingSphere getBoundingSphere() const = 0;

    private:
        void updateModel();

        glm::mat4 m_model;
        glm::mat4 m_modelInv;
        glm::vec3 m_pos;
        glm::vec3 m_rot;
};

#endif
