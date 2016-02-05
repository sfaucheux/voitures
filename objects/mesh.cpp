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
        vector<vec3> v ;
        vector<vec2> t ;
        vector<unsigned int> vi ;
        vector<unsigned int> ti ;
		std::map<glm::uvec2,unsigned int, comp> knowns ; //,comp> knowns;

		//Charge les données brutes dans des vecteurs temporaires
		loadRawData(&inFile, v, vi, t, ti);

		if (v.size() == t.size()) //On traite les données pour être texture-compatibles s'il y a lieu
		{
			cout << "loading with textures" << endl;
            cout << "processing UV data..." << endl;
            for (int i = 0; i < vi.size(); i++)
            {
                map<uvec2,unsigned int>::iterator it;

                //Has the couple (vert,uv) already been seen ?
                it = knowns.find(uvec2(vi[i], ti[i]));

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

                    cout << v.size() << " " << t.size() << endl;
                    m_vertices.push_back(v.at(vi[i]));
                    m_uvmap.push_back(t.at(ti[i]));
                    m_indices.push_back(m_vertices.size() - 1);

                    knowns[uvec2(vi[i],ti[i])] = m_vertices.size() - 1;
                }

            }
    cout << "done" << endl;

			m_gObj.load(m_vertices, m_indices, m_uvmap);
		}
		else
			m_gObj.load(v, vi); //Les donées brutes suffisent s'il n'y a pas de textures
		m_pObj = new PObject(); // = new PMesh();
		cout << "Loading successful" << endl;
	}
	else
		cout << "Error while loading model, no file found" << endl;
    inFile.clear();
    inFile.seekg(0, ios::beg); 

	m_vertices.clear();
	m_vertices.shrink_to_fit();

	m_indices.clear();
	m_indices.shrink_to_fit();

	m_uvmap.clear();
	m_uvmap.shrink_to_fit();

	m_normals.clear();
	m_normals.shrink_to_fit();
}



void Mesh::loadRawData(std::ifstream* filename, std::vector<glm::vec3> &v,std::vector<unsigned int> &vi, std::vector<glm::vec2> &t,std::vector<unsigned int> &ti )
{
	cout << "loading raw data from obj file..." << endl;

	string line;
	string ident;
	vec3 point;
	vec2 UV;

	//Temporary vectors filled with vertices and uvs, they are not necessarily in the same order

	while (getline(*filename, line))
	{
		stringstream ss (stringstream::in | stringstream::out);
		ss << line;

		ss >> ident;

		if (ident == "v")
		{
			ss >> point.x >> point.y >> point.z;
			v.push_back(point);
			cout << "vert: " << point.x << " " << point.y << " " << point.z << endl;
		}
		else if (ident == "vt")
		{
			ss >> UV.x >> UV.y;
			t.push_back(UV);
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

			vi.push_back(vert[0]);
			vi.push_back(vert[1]);
			vi.push_back(vert[2]);

			ti.push_back(uvs[0]);
			ti.push_back(uvs[1]);
			ti.push_back(uvs[2]);



			if(c == 4)
			{
				vi.push_back(vert[0]);
				vi.push_back(vert[2]);
				vi.push_back(vert[3]);

				ti.push_back(uvs[0]);
				ti.push_back(uvs[2]);
				ti.push_back(uvs[3]);


			}
		}
	}
	cout << "Loaded " << v.size() << " vertices, " << vi.size() << " indices"  << endl;
}

Mesh::~Mesh()
{
	delete m_pObj;
}

Object::ObjectType Mesh::getType()
{
	return Object::Mesh;
}
