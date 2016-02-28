#include "pmesh.h"

using namespace std;
using namespace glm;

PMesh::PMesh(Coordinates& coord) : PObject(coord)
{
}

bool PMesh::collide(PObject* obj)
{
    return obj->collideWithMesh(this);
}

bool PMesh::collideWithSphere(PSphere *s)
{
    return false; 
}

bool PMesh::collideWithBox(PBox* b)
{
    return false; 
}

bool PMesh::collideWithMesh(PMesh* b)
{
    return false; 
}

vector<tuple<vec3,vec3>> PMesh::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithMesh(this);
}

vector<tuple<vec3,vec3>> PMesh::collisionPointsWithBox(PBox* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PMesh::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> PMesh::collisionPointsWithSphere(PSphere* obj) 
{
    return vector<tuple<vec3,vec3>>();
}
