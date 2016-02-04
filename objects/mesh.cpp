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

	if (inFile.is_open())
	{

		//Charge les données brutes dans des vecteurs temporaires
		loadRawData(&inFile);

		if (vertTmp.size() == uvsTmp.size()) //On traite les données pour être texture-compatibles s'il y a lieu
		{
			cout << "loading with textures" << endl;
			processData();
			m_gObj.load(m_vertices, m_indices, m_uvmap);
		}
		else
			m_gObj.load(vertTmp, facesIDTmp); //Les donées brutes suffisent s'il n'y a pas de textures
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


void Mesh::processData()
{
	cout << "processing UV data..." << endl;
	for (int i = 0; i < m_indices.size(); i++)
	{
		addCouple(facesIDTmp.at(i), uvsIDTmp.at(i));
	}
	cout << "done" << endl;
}


//Add a couple of (vertex, UV) and its index in the arrays. Avoid redundancy of data
void Mesh::addCouple(unsigned int vertID, unsigned int uvID)
{
	//cout << "Adding couple : " << vertID << " - " << uvID  << endl;
	map<uvec2,unsigned int>::iterator it;

	//Has the couple (vert,uv) already been seen ?
	it = knowns.find(uvec2(vertID, uvID));

	if (it != knowns.end())
	{
		//cout << "couple known" << endl;
		//If yes, all we have to do is add the index we stored in the indices array
		m_indices.push_back(it->second);
	}
	else
	{
		//If no, we add a new couple of (vertex,uv) to the definitive array, a new index
		//pointing to this couple and we declare the couple in the "knowns" map.

		cout << vertTmp.size() << " " << uvsTmp.size() << endl;
		m_vertices.push_back(vertTmp.at(vertID));
		m_uvmap.push_back(uvsTmp.at(uvID));
		m_indices.push_back(m_vertices.size() - 1);

		knowns[uvec2(vertID,uvID)] = m_vertices.size() - 1;
	}
}

void Mesh::loadRawData(ifstream* inFile)
{
	cout << "loading raw data from obj file..." << endl;

	string line;
	string ident;
	vec3 point;
	vec2 UV;

	//Temporary vectors filled with vertices and uvs, they are not necessarily in the same order

	while (getline(*inFile, line))
	{
		stringstream ss (stringstream::in | stringstream::out);
		ss << line;

		ss >> ident;

		if (ident == "v")
		{
			ss >> point.x >> point.y >> point.z;
			vertTmp.push_back(point);
			cout << "vert: " << point.x << " " << point.y << " " << point.z << endl;
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
			int vert[4], uvs[4] = {0,0,0,0};
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
								cout << "ind: " << vert[c] << endl;
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

			facesIDTmp.push_back(vert[0]);
			facesIDTmp.push_back(vert[1]);
			facesIDTmp.push_back(vert[2]);

			uvsIDTmp.push_back(uvs[0]);
			uvsIDTmp.push_back(uvs[1]);
			uvsIDTmp.push_back(uvs[2]);



			if(c == 4)
			{
				facesIDTmp.push_back(vert[0]);
				facesIDTmp.push_back(vert[2]);
				facesIDTmp.push_back(vert[3]);

				uvsIDTmp.push_back(uvs[0]);
				uvsIDTmp.push_back(uvs[2]);
				uvsIDTmp.push_back(uvs[3]);


			}
		}
	}
	cout << "Loaded " << vertTmp.size() << " vertices, " << facesIDTmp.size() << " indices"  << endl;
}

Mesh::~Mesh()
{
	delete m_pObj;
}

Object::ObjectType Mesh::getType()
{
	return Object::Mesh;
}
