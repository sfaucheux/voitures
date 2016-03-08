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
        
        std::vector<glm::vec3> getVertices();
        std::vector<glm::uvec3> getIndices();

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Sphere *s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* m) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m) const;


    private:
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::uvec3> m_faces;
        std::vector<int> m_normals;

};

#endif
