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
        std::vector<glm::uvec3> m_faces;
        std::vector<int> m_normals;

};

#endif
