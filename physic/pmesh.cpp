#include "pmesh.h"

PMesh::PMesh()
{
}

bool PMesh::collide(PObject* obj)
{
    return obj->collideWithMesh(this);
}

bool PMesh::collideWithSphere(PSphere *s)
{
    return -1; 
}

bool PMesh::collideWithBox(PBox* b)
{
    return -1;
}

bool PMesh::collideWithMesh(PMesh* b)
{
    return -1;
}
