#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mesh.h"

#include "collisions.h"

using namespace std;
using namespace glm;

Mesh::Mesh(const char* filename)
{
	cout << "Loading " << filename << endl;

	ifstream inFile ("models/" + string(filename));

	if (inFile.is_open())
	{
        vector<vec2> traw;
        vector<unsigned int> tiraw;
		std::map<glm::uvec2,unsigned int, comp> knowns ; //,comp> knowns;

		//Charge les données brutes dans des vecteurs temporaires
		loadRawData(&inFile, m_vraw, m_viraw, traw, tiraw);

		if (tiraw.size() == m_viraw.size()) //On traite les données pour être texture-compatibles s'il y a lieu
		{
			cout << "loading with textures" << endl;
            cout << "processing UV data..." << endl;
            for (int i = 0; i < m_viraw.size(); i++)
            {
                map<uvec2,unsigned int>::iterator it;

                //Has the couple (vert,uv) already been seen ?
                it = knowns.find(uvec2(m_viraw[i], tiraw[i]));

                if (it != knowns.end())
                {
                    //cout << "couple known" << endl;
                    //If yes, all we have to do is add the index we stored in the indices array
                    m_id.push_back(it->second);
                }
                else
                {
                    //If no, we add a new couple of (vertex,uv) to the definitive array, a new index
                    //pointing to this couple and we declare the couple in the "knowns" map.

                    //cout << m_v.size() << " " << m_t.size() << endl;
                    m_id.push_back(m_v.size());
                    knowns[uvec2(m_viraw[i], tiraw[i])] = m_v.size();

                    m_v.push_back(m_vraw.at(m_viraw[i]));
                    m_t.push_back(traw.at(tiraw[i]));
                }

            }
            cout << "done" << endl;
            m_hasTextures = true;
		}
		else
        {
            m_hasTextures = false;
        }
		cout << "Loading successful" << endl;
	}
	else
		cout << "Error while loading model, no file found" << endl;
    inFile.clear();
    inFile.seekg(0, ios::beg); 
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
			//cout << "vert: " << point.x << " " << point.y << " " << point.z << endl;
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
            bool tex = false ;

			while (cur != "" && c < 4)
			{
				cur = "";
				ss >> cur;
				stringstream subss (stringstream::in | stringstream::out);
				subss << cur;
				fLineInd = 0;

				while (getline(subss, subcur, '/'))
				{
                    //si f x//y il faudrait l'enlever.
					if (subcur != "")
					{
						switch (fLineInd)
						{
							case 0:
								vert[c] = stoi(subcur) - 1;
								//cout << "ind: " << vert[c] << endl;
								break;

							case 1:
								uvs[c] = stoi(subcur) - 1;
                                tex = true ;
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
            
            if(tex)
            {
                ti.push_back(uvs[0]);
                ti.push_back(uvs[1]);
                ti.push_back(uvs[2]);
            }


			if(c == 4)
			{
				vi.push_back(vert[0]);
				vi.push_back(vert[2]);
				vi.push_back(vert[3]);
                if(tex)
                {
                    ti.push_back(uvs[0]);
                    ti.push_back(uvs[2]);
                    ti.push_back(uvs[3]);
                }

			}
		}
	}
    /*
    for(int i = 0 ; i < vi.size()/3 ; i++)
    {
        cout << vi[3*i] << ";" << vi[3*i+1] << ";" << vi[3*i+2] << endl ;
    }*/
	cout << "Loaded " << v.size() << " vertices with " << vi.size() << " indices, "<< t.size() << " uvs with "<< ti.size() << " indices."  << endl;
}

Mesh::~Mesh()
{
}

std::vector<vec3> Mesh::getVertices()
{
    if (m_hasTextures)
        return m_v;
    return m_vraw;
}

std::vector<unsigned int> Mesh::getIndices()
{
    if (m_hasTextures)
        return m_id;
    return m_viraw;
}

std::vector<vec2>* Mesh::getTextures()
{
    if (m_hasTextures)
        return &m_t;
    return nullptr;
}

bool Mesh::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Mesh::collide(const Sphere* s) const
{
    return Collisions::collide(this, s);
}

bool Mesh::collide(const Box* b) const
{
    return Collisions::collide(this, b);
}

bool Mesh::collide(const Mesh* m) const
{
    return Collisions::collide(this, m);
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Sphere* s) const
{
    return Collisions::collisionPoints(this, s);
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Box* b) const
{
    return Collisions::collisionPoints(this, b);
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Mesh* m) const
{
    return Collisions::collisionPoints(this, m);
}
AABB Mesh::getAABB() const
{
    //TODO
    cerr << "Mesh : AABB non implémentée." << endl ;
    return AABB(vec3(1));
}
BoundingSphere Mesh::getBoundingSphere() const
{
    //TODO
    cerr << "Mesh : Bounding Sphere non implémentée." << endl ;
    return BoundingSphere(1);
}
