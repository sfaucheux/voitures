#ifndef Mesh_H
#define Mesh_H

#include <string>
#include <vector>

#include "../glm/glm.hpp"

class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();

		virtual void loadObject(std::string filename);

        const std::vector<glm::vec3>& getVertices() const;
        const std::vector<glm::uvec3>& getIndices() const;


	private:
		std::vector<glm::vec3> m_vertices;
        std::vector<glm::uvec3> m_faces;
        std::vector<int> m_normals;

};

#endif
