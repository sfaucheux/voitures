#ifndef Mesh_H
#define Mesh_H

#include <string>
#include <vector>
#include <map>

#include "../glm/glm.hpp"

#include "object.h"

class Mesh : public Object
{
	public:
		Mesh(std::string filename);
		virtual ~Mesh();

        ObjectType getType();


	private:
		std::vector<glm::vec3> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<glm::vec2> m_uvmap;
        std::vector<unsigned int> m_normals;

		void loadRawData(std::ifstream* filename, std::vector<glm::vec3>& v,std::vector<unsigned int>& vi, std::vector<glm::vec2>& t,std::vector<unsigned int>& ti );
		void processData(std::vector<glm::vec3>& v,std::vector<unsigned int>& vi, std::vector<glm::vec2>& t,std::vector<unsigned int>& ti );;

        struct comp
		{
			bool operator()(const glm::uvec2& a, const glm::uvec2& b) const
			{
				return a.x < b.x;
			}
		};

};

#endif
