#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../glm/glm.hpp"
#include "vector"
#include "tuple"

class Geometry
{
    public:
        Geometry();
        ~Geometry();

        glm::vec3 getPosition() const;
        glm::vec3 getRotation() const;
        glm::mat4 const& getModel() const;

        void translate(glm::vec3 translation);
        void rotate(glm::vec3 rotation);
        glm::vec3 getLocalPoint(const glm::vec3& point) const;

        virtual bool collide(const Geometry* obj) const = 0 ;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const = 0 ;


    private:
        void updateModel();

        glm::mat4 m_model;
        glm::mat4 m_modelInv;
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_homoth;
};

#endif
