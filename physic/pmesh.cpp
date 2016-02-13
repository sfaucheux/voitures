#include "pmesh.h"

using namespace std;
using namespace glm;

PMesh::PMesh()
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

vector<vec3> PMesh::collisionPoints(PObject* obj)
{
    return obj->collisionPointsWithMesh(this);
}

vector<vec3> PMesh::collisionPointsWithBox(PBox* obj) 
{
    return vector<vec3>();
}

vector<vec3> PMesh::collisionPointsWithMesh(PMesh* obj) 
{
    return vector<vec3>();
}

vector<vec3> PMesh::collisionPointsWithSphere(PSphere* obj) 
{
    return vector<vec3>();
}
