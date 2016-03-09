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
        Mesh(const char* filename);
        virtual ~Mesh();
        
        std::vector<glm::vec3> getVertices();
        std::vector<unsigned int> getIndices();
        std::vector<glm::vec2>* getTextures();

        virtual bool collide(const Geometry* obj) const;
        bool collide(const Sphere* s) const;
        bool collide(const Box* b) const;
        bool collide(const Mesh* m) const;

        virtual std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Geometry* obj) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Sphere* s) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Box* b) const;
        std::vector<std::tuple<glm::vec3,glm::vec3>> collisionPoints(const Mesh* m) const;


    private:
		void loadRawData(std::ifstream* filename, std::vector<glm::vec3>& v,std::vector<unsigned int>& vi, std::vector<glm::vec2>& t,std::vector<unsigned int>& ti );

        struct comp
		{
			bool operator()(const glm::uvec2& a, const glm::uvec2& b) const
			{
				return a.x < b.x || ((a.x == b.x) && (a.y < a.y)) ;
			}
		};

        bool m_hasTextures;
        std::vector<glm::vec3> m_vraw, m_v;
        std::vector<glm::vec2> m_t;
        std::vector<unsigned int> m_viraw, m_id;

};

#endif
