#ifndef Mesh_H
#define Mesh_H

#include <string>
#include <vector>

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

		//Super bof de déclarer ceux-là en membres de la classe, mais bon...

		struct comp
		{
			bool operator()(const glm::uvec2& a, const glm::uvec2& b) const
			{
				return a.x < b.x;
			}
		};

		void addCouple(unsigned int vertID, unsigned int uvID);
		std::map<glm::uvec2,unsigned int,comp> knowns;
		std::vector<glm::vec3> vertTmp;
		std::vector<glm::vec2> uvsTmp;

};

#endif
