#include <iostream>
#include <fstream>
#include <sstream>

#include "mesh.h"

#include "collisions.h"

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
        cout << "Loading successful" << endl;
    }
    else
        cout << "Error while loading model, no file found" << endl;
}

std::vector<vec3> Mesh::getVertices()
{
    return m_vertices;
}

std::vector<uvec3> Mesh::getIndices()
{
    return m_faces;
}

bool Mesh::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Mesh::collide(const Sphere *s) const
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
