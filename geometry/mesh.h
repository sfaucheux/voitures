#ifndef Mesh_H
#define Mesh_H

#include "geometry.h"
#include <string>

class Box;
class Sphere;

class Mesh : public Geometry 
{
    public:
        Mesh(std::string filename);
        virtual bool collide(const Geometry* obj) const;
        bool collide(const Sphere *s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* b) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* obj) const;
        
        const std::string getFileName() const ;

    private:
        std::string m_fileName ;

};

#endif
