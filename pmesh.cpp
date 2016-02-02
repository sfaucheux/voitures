#include "pmesh.h"

using namespace std;
using namespace glm;

PMesh::PMesh()
{
}

//Load a default mesh
void PMesh::loadObject()
{
    loadObject("cube.obj");
}

void PMesh::loadObject(string filename)
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
                //cout << line << endl;
                ss >> point.x >> point.y >> point.z;
                cout << "Loaded vertex " << point.x << " " << point.y << " " << point.z << endl;

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

                cout << "loading face ";
                while (cur != "" && c < 4)
                {
                    cout << "*";
                    cur = "";
                    ss >> cur;
                    stringstream subss (stringstream::in | stringstream::out);
                    subss << cur;
                    getline(subss, subcur, '/');
                    vert[c] = stof(subcur);
                    c++;
                }
                cout << endl;

                face.x = vert[0];
                face.y = vert[1];
                face.z = vert[2];

                m_faces.push_back(face);
                cout << "Loaded face " << face.x << " " << face.y << " " << face.z << endl;

                if(c == 4)
                {
                    face.y = face.z;
                    face.z = vert[3];
                    m_faces.push_back(face);
                    cout << "Loaded face " << face.x << " " << face.y << " " << face.z << endl;
                }
            }
        }
    }
}

const vector<glm::vec3>& PMesh::getVertices() const
{
    return m_vertices;
}

const vector<glm::uvec3>& PMesh::getIndices() const
{
    return m_faces;
}

PMesh::~PMesh()
{
}
