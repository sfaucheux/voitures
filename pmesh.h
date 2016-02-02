#ifndef PMesh_H
#define PMesh_H

#include "pobject.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Face
{
    int A,B,C;
};

class PMesh : public PObject
{
	public:
		PMesh();

        virtual void loadObject();
		virtual void loadObject(std::string filename);

		virtual ~PMesh();
	private:
		std::vector<glm::vec3> m_vertices;
        std::vector<Face> m_faces;
        std::vector<int> m_normals;
};

#endif
