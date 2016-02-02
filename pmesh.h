#ifndef PMesh_H
#define PMesh_H

#include "pobject.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class PMesh : public PObject
{
	public:
		PMesh();

        virtual void loadObject();
		virtual void loadObject(std::string filename);

        const std::vector<glm::vec3>& getVertices() const;
        const std::vector<glm::uvec3>& getIndices() const;

		virtual ~PMesh();
	private:
		std::vector<glm::vec3> m_vertices;
        std::vector<glm::uvec3> m_faces;
        std::vector<int> m_normals;
};

#endif
