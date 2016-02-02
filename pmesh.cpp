#include "pmesh.h"

using namespace std;
using namespace glm;

PMesh::PMesh()
{
}

//Load a default mesh
void PMesh::loadObject()
{
    loadObject("suzanne.obj");
}

void PMesh::loadObject(string filename)
{
	cout << "Loading " << filename << endl;
    ifstream inFile ("models/" + filename);
    string line;

    if (inFile.is_open())
    {
        char ident;
        Face face;
        int normal;
        vec3 point;

        while (getline(inFile, line))
        {
            stringstream ss (stringstream::in | stringstream::out);
            ss << line;
            
            ss >> ident;

            switch (ident)
            {
                case 'v':
                    //cout << line << endl;
                    ss >> point.x >> point.y >> point.z;
                    cout << "Loaded vertex " << point.x << " " << point.y << " " << point.z << endl;

                    m_vertices.push_back(point);
                    break;

                case 'f':
                    ss >> face.A >> face.B >> face.C;
                    face.A --;
                    face.B --;
                    face.C --;

                    ss >> normal;
                    normal --;

                    m_faces.push_back(face);
                    m_normals.push_back(normal);

                    cout << "Loaded face " << face.A << " " << face.B << " " << face.C << endl;
                    cout << "Loaded normal " << normal << endl;
                    break;
            }
        }
    }
}

PMesh::~PMesh()
{
}
