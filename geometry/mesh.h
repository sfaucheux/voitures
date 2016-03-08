#ifndef Mesh_H
#define Mesh_H

#include <string>
#include "../glm/glm.hpp"
#include "geometry.h"

class Box;
class Sphere;

class Mesh : public Geometry 
{
    public:
        Mesh(std::string filename);
        virtual ~Mesh();
        
        std::vector<glm::vec3> getVertices();
        std::vector<glm::uvec3> getIndices();


        virtual bool collide(const Geometry* obj) const;
        virtual bool collideWithSphere(const Sphere* obj) const;
        virtual bool collideWithBox(const Box* obj) const;
        virtual bool collideWithMesh(const Mesh* obj) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithSphere(const Sphere* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithBox(const Box* obj) const;
        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPointsWithMesh(const Mesh* obj) const;
       

    private:
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::uvec3> m_faces;
        std::vector<int> m_normals;

};

#endif
