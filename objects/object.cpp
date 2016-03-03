#include "object.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#define GET_INDEX(i, j) ((i) * (nbPoints / 2) + (j))

using namespace std ;
using namespace glm ;

Object::Object(Sphere s)
{
    float radius = s.getRadius();
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    static const int nbPointsUnitSphere = 3;
    int nbPoints = radius * nbPointsUnitSphere;
    float dAngle = 2.0 * M_PI / (float)nbPoints;
    int topVertexIndex = nbPoints * (nbPoints / 2);

    for (int i = 0; i < nbPoints; i++) 
    {
        for (int j = 0; j < nbPoints / 2; j++)
        {
            float theta = i * dAngle;
            float phi = j * dAngle - (M_PI / 2.0);
            vertices.push_back(glm::vec3(radius * cos(theta) * cos(phi), radius * sin(theta) * cos(phi), radius * sin(phi)));
            int nextI = (i < nbPoints - 1) ? i + 1 : 0;
            int a = GET_INDEX(i, j);
            int b = GET_INDEX(nextI, j);
            int nextJ = (j < (nbPoints / 2) - 1) ? j + 1 : j;
            int c = (j == nextJ) ? topVertexIndex : GET_INDEX(i, nextJ);
            int d = (j == nextJ) ? topVertexIndex : GET_INDEX(nextI, nextJ);
            indices.push_back(glm::uvec3(a, b, c));
            indices.push_back(glm::uvec3(b, d, c));
        }
    }
    vertices.push_back(glm::vec3(0, 0, radius));

    m_gObj.load(vertices, indices);
    m_pObj = new PObject(s);
    m_pObj->setInertia(mat3(2*m_pObj->getMass()*radius*radius/5.));

}
Object::Object(Box b)
{
    float w = b.getWidth(), h = b.getHeight(), d = b.getDepth() ;
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    vertices.push_back(vec3( w / 2, -h / 2, -d / 2));
    vertices.push_back(vec3( w / 2, -h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2, -h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2, -h / 2, -d / 2));
    vertices.push_back(vec3( w / 2,  h / 2, -d / 2));
    vertices.push_back(vec3( w / 2,  h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2,  h / 2,  d / 2));
    vertices.push_back(vec3(-w / 2,  h / 2, -d / 2));

    indices.push_back(uvec3(0, 1, 2));
    indices.push_back(uvec3(0, 2, 3));
    indices.push_back(uvec3(4, 7, 6));
    indices.push_back(uvec3(4, 6, 5));
    indices.push_back(uvec3(0, 4, 5));
    indices.push_back(uvec3(0, 5, 1));
    indices.push_back(uvec3(1, 5, 6));
    indices.push_back(uvec3(1, 6, 2));
    indices.push_back(uvec3(2, 6, 7));
    indices.push_back(uvec3(2, 7, 3));
    indices.push_back(uvec3(4, 0, 3));
    indices.push_back(uvec3(4, 3, 7));

    m_gObj.load(vertices, indices);
    m_pObj = new PObject(b);
    mat3 inertia(0);
    inertia[0][0] = m_pObj->getMass()*(h*h + d*d)/12.;
    inertia[1][1] = m_pObj->getMass()*(w*w + d*d)/12.;
    inertia[2][2] = m_pObj->getMass()*(h*h + w*w)/12.;
    m_pObj->setInertia(inertia);
}

Object::Object(Mesh m)
{
    vector<vec3> m_vertices;
    vector<uvec3> m_faces;
    vector<int> m_normals;
    string filename = m.getFileName();
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
        m_pObj = new PObject(m);
        cout << "Loading successful" << endl;
    }
    else
        cout << "Error while loading model, no file found" << endl;

}
Object::~Object()
{
    delete m_pObj ;
}
void Object::setShader(Shader* shader)
{
    m_gObj.setShader(shader);
}

PObject* Object::getPObject()
{
    return m_pObj;
}

Drawable const& Object::getDrawable() const
{
    return m_gObj;
}

const Shader* Object::getShader() const
{
    return m_gObj.getShader();
}

void Object::sync()
{
    m_gObj.setModel(m_pObj->getModel());
}

void Object::translate(glm::vec3 t)
{
    m_pObj->translate(t);
    this->sync();
}

void Object::rotate(glm::vec3 r)
{
    m_pObj->rotate(r);
    this->sync();
}
