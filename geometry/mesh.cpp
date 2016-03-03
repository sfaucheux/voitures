#include "mesh.h"

#include "collisions.h"

using namespace std;
using namespace glm;

Mesh::Mesh(string fileName)
{
    m_fileName = fileName ;
}
const string Mesh::getFileName() const
{
    return m_fileName ;
}

bool Mesh::collide(const Geometry* obj) const
{
    return obj->collide(this);
}

bool Mesh::collide(const Sphere *s) const
{
    return false; 
}

bool Mesh::collide(const Box* b) const
{
    return false; 
}

bool Mesh::collide(const Mesh* b) const
{
    return false; 
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Geometry* obj) const
{
    return obj->collisionPoints(this);
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Box* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Mesh* obj) const
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Mesh::collisionPoints(const Sphere* obj) const
{
    return vector<tuple<vec3,vec3>>();
}
