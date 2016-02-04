#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "mesh.h"

using namespace std;
using namespace glm;


Mesh::Mesh(string filename)
{
	cout << "Loading " << filename << endl;
	ifstream inFile ("models/" + filename);
	string line;

	if (inFile.is_open())
	{
		string ident;
		vec3 point;
		vec2 UV;

		//Temporary vectors filled with vertices and uvs, they are not necessarily in the same order

		while (getline(inFile, line))
		{
			stringstream ss (stringstream::in | stringstream::out);
			ss << line;

			ss >> ident;

			if (ident == "v")
			{
				ss >> point.x >> point.y >> point.z;
				vertTmp.push_back(point);
			}
			else if (ident == "vt")
			{
				ss >> UV.x >> UV.y;
				uvsTmp.push_back(UV);
			}
			else if (ident == "f")
			{
				int c = 0;
				int fLineInd = 0;
				int vert[4], uvs[4];
				uvec3 face;
				uvec3 uvFace;
				string cur = "plop";
				string subcur;

				while (cur != "" && c < 4)
				{
					cur = "";
					ss >> cur;
					stringstream subss (stringstream::in | stringstream::out);
					subss << cur;
					fLineInd = 0;

					while (getline(subss, subcur, '/'))
					{
						if (subcur != "")
						{
							switch (fLineInd)
							{
								case 0:
									vert[c] = stoi(subcur) - 1;
									break;

								case 1:
									uvs[c] = stoi(subcur) - 1;
									break;

								case 2:
									break;

								default:
									cout << "Warning, weird stuff in obj file" << endl;
							}
						}
						fLineInd ++;
					}
					c++;
				}

				addCouple(vert[0],uvs[0]);
				addCouple(vert[1],uvs[1]);
				addCouple(vert[2],uvs[2]);

				/*m_faces.push_back(vert[0]);
				  m_faces.push_back(vert[1]);
				  m_faces.push_back(vert[2]);

				  m_uvindices.push_back(uvs[0]);
				  m_uvindices.push_back(uvs[1]);
				  m_uvindices.push_back(uvs[2]);*/

				if(c == 4)
				{
					addCouple(vert[0],uvs[0]);
					addCouple(vert[2],uvs[2]);
					addCouple(vert[3],uvs[3]);
					/*m_faces.push_back(vert[0]);
					  m_faces.push_back(vert[2]);
					  m_faces.push_back(vert[3]);

					  m_uvindices.push_back(uvs[0]);
					  m_uvindices.push_back(uvs[2]);
					  m_uvindices.push_back(uvs[3]);*/
				}
			}
		}

		m_gObj.load(m_vertices, m_indices, m_uvmap); //TODO
		m_pObj = new PObject(); // = new PMesh();
		cout << "Loading successful" << endl;
	}
	else
		cout << "Error while loading model, no file found" << endl;

	m_vertices.clear();
	m_vertices.shrink_to_fit();

	m_indices.clear();
	m_indices.shrink_to_fit();

	m_uvmap.clear();
	m_uvmap.shrink_to_fit();

	m_normals.clear();
	m_normals.shrink_to_fit();
}

//Add a couple of (vertex, UV) and its index in the arrays. Avoid redundancy of data
void Mesh::addCouple(unsigned int vertID, unsigned int uvID)
{
	map<uvec2,unsigned int>::iterator it;

	//Has the couple (vert,uv) already been seen ?
	it = knowns.find(uvec2(vertID, uvID));

	if (it == knowns.end())
	{
		//If yes, all we have to do is add the index we stored in the indices array
		m_indices.push_back(it->second);
	}
	else
	{
		//If no, we add a new couple of (vertex,uv) to the definitive array, a new index
		//pointing to this couple and we declare the couple in the "knowns" map.

		m_vertices.push_back(vertTmp.at(vertID));
		m_uvmap.push_back(uvsTmp.at(uvID));
		m_indices.push_back(m_vertices.size() - 1);

		knowns[uvec2(vertID,uvID)] = m_vertices.size() - 1;
	}
}

Mesh::~Mesh()
{
    delete m_pObj;
}

Object::ObjectType Mesh::getType()
{
    return Object::Mesh;
}
