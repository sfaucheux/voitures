#include <iostream>
#include <fstream>
#include <sstream>

#include "mesh.h"
#include "../physic/pmesh.h"

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

        while (getline(inFile, line))
        {
            stringstream ss (stringstream::in | stringstream::out);
            ss << line;

            ss >> ident;

            if (ident == "v")
            {
                ss >> point.x >> point.y >> point.z;
                m_vertices.push_back(point);
            }
            else if (ident == "f")
            {
                int c = 0;
                int last;
                int vert[4];
                uvec3 face;
                string cur = "plop";
                string subcur;

                while (cur != "" && c < 4)
                {
                    cur = "";
                    ss >> cur;
                    stringstream subss (stringstream::in | stringstream::out);
                    subss << cur;
                    getline(subss, subcur, '/');
                    if (subcur != "")
                    {
                        vert[c] = stoi(subcur) - 1;
                        c++;
                    }
                }

                face.x = vert[0];
                face.y = vert[1];
                face.z = vert[2];

                m_faces.push_back(face);

                if(c == 4)
                {
                    face.y = face.z;
                    face.z = vert[3];
                    m_faces.push_back(face);
                }
            }
        }
        m_gObj.load(m_vertices, m_faces);
        m_pObj = new PMesh();
        cout << "Loading successful" << endl;
    }
    else
        cout << "Error while loading model, no file found" << endl;
}

Mesh::~Mesh()
{
    delete m_pObj;
}

Object::ObjectType Mesh::getType()
{
    return Object::Mesh;
}
