#include "pmesh.h"

PMesh::PMesh()
{
}
int PMesh::collide(PObject* obj)
{
    return obj->collideWithMesh(this);
}
int PMesh::collideWithSphere(PSphere *s)
{
    return -1 ; 
}
int PMesh::collideWithBox(PBox* b)
{
    return -1 ;
}
int PMesh::collideWithMesh(PMesh* b)
{
    return -1 ;
}
