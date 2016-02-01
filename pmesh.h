#ifndef PMesh_H
#define PMesh_H

#include "pobject.h"
#include <vector>
#include <iostream>

class PMesh : public PObject
{
	public:
		PMesh();

		void loadObject(std::string filename);

		virtual ~PMesh();
	private:
		std::vector<float> m_mesh;
};

#endif
