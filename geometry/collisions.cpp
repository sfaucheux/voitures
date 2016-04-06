#include "collisions.h"
#include "../glm/gtx/norm.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_access.hpp"
#include <iostream>
#include <iomanip>

using namespace glm ;
using namespace std ;

float square(float f)
{
    return f * f;
}

float sgn(float f)
{
    if (f < 0)
        return -1;
    else if (f > 0)
        return 1;
    return 0;
}

bool Collisions::collide(const Sphere* obj1, const Sphere* obj2)
{
    return distance2(obj1->getPosition(), obj2->getPosition()) <= square(obj1->getRadius() + obj2->getRadius());
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* obj1, const Sphere* obj2)
{
    //On retourne la moyenne des centres ponderees par les rayons.
    //La normale est définie comme le vecteur formé par les deux centres.
    //Suppose que les spheres sont en collision (c'est le cas, la broadphase est exacte pour les solides de base).
    vec3 point((obj1->getRadius() * obj1->getPosition() + obj2->getRadius() * obj2->getPosition()) / (obj1->getRadius() + obj2->getRadius()));
    vec3 normal(obj2->getPosition()- obj1->getPosition());
    return vector<tuple<vec3,vec3>>({make_tuple(point, normal)});
}

bool Collisions::collide(const Sphere* s, const Box* b)
{
    // calculating s's position relative to b
    glm::vec3 sphPos = b->getLocalPoint(s->getPosition());

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= b->getWidth() / 2.0)
    {
        if (yc <= b->getHeight() / 2.0)
            return zc - r <= b->getDepth() / 2.0;
        if (zc <= b->getDepth() / 2.0)
            return yc - r <= b->getHeight() / 2.0;
        if (yc <= b->getHeight() / 2.0 + r)
            return square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
        return false;
    }
    else if (yc <= b->getHeight() / 2.0)
    {
        if (zc <= b->getDepth() / 2.0)
            return xc - r <= b->getWidth() / 2.0;
        if (zc <= b->getDepth() / 2.0 + r)
            return square(xc - (b->getWidth() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
        return false;
    }
    else if (zc <= b->getDepth() / 2.0)
    {
        if (xc <= b->getWidth() / 2.0 + r)
            return square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) <= square(r);
        return false;
    }
    else if ((xc <= b->getWidth() / 2.0 + r) && (yc <= b->getHeight() / 2.0 + r) && (zc <= b->getDepth() / 2.0 + r))
        return square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r);
    return false;
}

bool Collisions::collide(const Box* b, const Sphere* s)
{
    return collide(s, b);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* s, const Box* b)
{
    glm::vec3 collisionPoint;
    // calculating s's position relative to b
    glm::vec3 sphPos = b->getLocalPoint(s->getPosition());

    float xc = fabsf(sphPos.x);
    float yc = fabsf(sphPos.y);
    float zc = fabsf(sphPos.z);
    float r = s->getRadius();
    if (xc <= b->getWidth() / 2.0)
    {
        if (yc <= b->getHeight() / 2.0)
        {
            if (zc - r <= b->getDepth() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.z) * glm::vec3(0, 0, r);
        }
        else if (zc <= b->getDepth() / 2.0)
        {
            if (yc - r <= b->getHeight() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.y) * glm::vec3(0, r, 0);
        }
        else if (yc <= b->getHeight() / 2.0 + r)
        {
            if (square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sphPos.x, sgn(sphPos.y) * b->getHeight() / 2.0, sgn(sphPos.z) * b->getDepth() / 2.0);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (yc <= b->getHeight() / 2.0)
    {
        if (zc <= b->getDepth() / 2.0)
        {
            if (xc - r <= b->getWidth() / 2.0)
                collisionPoint = sphPos - sgn(sphPos.x) * glm::vec3(r, 0, 0);
        }
        else if (zc <= b->getDepth() / 2.0 + r)
        {
            if (square(xc - (b->getWidth() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sphPos.y, sgn(sphPos.z) * b->getDepth() / 2.0);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if (zc <= b->getDepth() / 2.0)
    {
        if (xc <= b->getWidth() / 2.0 + r)
        {
            if (square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) <= square(r))
                collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sgn(sphPos.y) * b->getHeight() / 2.0, sphPos.z);
        }
        else
            return vector<tuple<vec3,vec3>>();
    }
    else if ((xc <= b->getWidth() / 2.0 + r) && (yc <= b->getHeight() / 2.0 + r) && (zc <= b->getDepth() / 2.0 + r))
    {
        if (square(xc - (b->getWidth() / 2.0)) + square(yc - (b->getHeight() / 2.0)) + square(zc - (b->getDepth() / 2.0)) <= square(r))
            collisionPoint = glm::vec3(sgn(sphPos.x) * b->getWidth() / 2.0, sgn(sphPos.y) * b->getHeight() / 2.0, sgn(sphPos.z) * b->getDepth() / 2.0);
    }
    else
    {
        return vector<tuple<vec3,vec3>>();
    }
    return vector<tuple<vec3,vec3>>({make_tuple(b->getWorldPoint(collisionPoint), mat3(b->getRotationMatrix()) * (collisionPoint - sphPos))});
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* b, const Sphere* s)
{
    vector<tuple<vec3,vec3>> r = collisionPoints(s,b);
    for(auto it = r.begin() ; it != r.end() ; it++)
    {
        get<1>(*it) = -get<1>(*it) ;
    }
    return r;
}

bool Collisions::collide(const Sphere* s, const Mesh* m)
{
    return false;
}

bool Collisions::collide(const Mesh* m, const Sphere* s)
{
    return collide(s, m);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Sphere* s, const Mesh* m)
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* m, const Sphere* s)
{
    return vector<tuple<vec3,vec3>>();
}
inline bool overlap(const Box* b1, const Box* b2, vec3 n)
{
    mat3 r1 = mat3(b1->getRotationMatrix());
    mat3 r2 = mat3(b2->getRotationMatrix());

    float c = dot(b1->getPosition(), n);
    float s = fabs(b1->getWidth() * dot(n, column(r1,0))) 
        + fabs(b1->getHeight() * dot(n, column(r1,1))) 
        + fabs(b1->getDepth() * dot(n, column(r1,2))) ;

    float min1 = c - s/2;
    float max1 = c + s/2;

    c = dot(b2->getPosition(), n);
    s = fabs(b2->getWidth() * dot(n, column(r2,0))) 
        + fabs(b2->getHeight() * dot(n, column(r2,1))) 
        + fabs(b2->getDepth() * dot(n, column(r2,2))) ;

    float min2 = c - s/2;
    float max2 = c + s/2;
    
    //Attention a bien garder l'inegalité sticte
    //Pour le cas ou n est le vecteur nul 
    return (max1 < min2 || min1 > max2);
}
inline float overlapDepth(const Box* b1, const Box* b2, vec3 n, bool& obj1Min)
{
    mat3 r1 = mat3(b1->getRotationMatrix());
    mat3 r2 = mat3(b2->getRotationMatrix());

    float c = dot(b1->getPosition(), n);
    float s = fabs(b1->getWidth() * dot(n, column(r1,0))) 
        + fabs(b1->getHeight() * dot(n, column(r1,1))) 
        + fabs(b1->getDepth() * dot(n, column(r1,2))) ;

    float min1 = c - s/2;
    float max1 = c + s/2;

    c = dot(b2->getPosition(), n);
    s = fabs(b2->getWidth() * dot(n, column(r2,0))) 
        + fabs(b2->getHeight() * dot(n, column(r2,1))) 
        + fabs(b2->getDepth() * dot(n, column(r2,2))) ;

    float min2 = c - s/2;
    float max2 = c + s/2;
   
    float min = (min1 > min2) ? min1 : min2 ;
    float max = (max1 < max2) ? max1 : max2 ;
    obj1Min = (min1 < min2);
    return fabs(max - min)/l2Norm(n);
}

bool Collisions::collide(const Box* obj1, const Box* obj2)
{
    mat3 r1 = mat3(obj1->getRotationMatrix());
    mat3 r2 = mat3(obj2->getRotationMatrix()); 

    //Normales de test (3 axes + 3 axes + produit vectoriel des axes 2 à 2)
    if(overlap(obj1,obj2,column(r1,0)))
        return false;
    if(overlap(obj1,obj2,column(r1,1)))
        return false;
    if(overlap(obj1,obj2,column(r1,2)))
        return false;
    if(overlap(obj1,obj2,column(r2,0)))
        return false;
    if(overlap(obj1,obj2,column(r2,1)))
        return false;
    if(overlap(obj1,obj2,column(r2,2)))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,0),column(r2,0))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,0),column(r2,1))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,0),column(r2,2))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,1),column(r2,0))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,1),column(r2,1))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,1),column(r2,2))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,2),column(r2,0))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,2),column(r2,1))))
        return false;
    if(overlap(obj1,obj2,cross(column(r1,2),column(r2,2))))
        return false;

    return true;
}
vector<tuple<vec3,vec3>> collisionEdges(const Box* b1, const Box* b2, int i, int j, bool obj1isMin, vec3 n)
{
    vec3 s1 = b1->getSize();
    vec3 s2 = b2->getSize();
    mat3 r1 = mat3(b1->getRotationMatrix());
    mat3 r2 = mat3(b2->getRotationMatrix());

    int x = i, y = (i+1)%3, z = (i+2)%3 ;
    vec3 vx(0), vy(0), vz(0);
    vx[x] = vy[y] = vz[z] = 1;
    vec3 p1, p2, p3, p4;
    if(obj1isMin == dot(n, column(r1, y)) > 0)
    {
        if(obj1isMin == dot(n, column(r1, z)) > 0)
        {
            p1 = b1->getWorldPoint(-s1[x]/2*vx + s1[y]/2*vy + s1[z]/2*vz);
            p2 = b1->getWorldPoint(s1[x]/2*vx + s1[y]/2*vy + s1[z]/2*vz);
        }
        else
        {
            p1 = b1->getWorldPoint(-s1[x]/2*vx + s1[y]/2*vy - s1[z]/2*vz);
            p2 = b1->getWorldPoint(s1[x]/2*vx + s1[y]/2*vy - s1[z]/2*vz);
        }
    }
    else
    {
        if(obj1isMin == dot(n, column(r1, z)) > 0)
        {
            p1 = b1->getWorldPoint(-s1[x]/2*vx - s1[y]/2*vy + s1[z]/2*vz);
            p2 = b1->getWorldPoint(s1[x]/2*vx - s1[y]/2*vy + s1[z]/2*vz);
        }
        else
        {
            p1 = b1->getWorldPoint(-s1[x]/2*vx - s1[y]/2*vy - s1[z]/2*vz);
            p2 = b1->getWorldPoint(s1[x]/2*vx - s1[y]/2*vy - s1[z]/2*vz);
        }
    }

    x = j;
    y = (j+1)%3;
    z = (j+2)%3 ;
    vx = vy = vz = vec3(0) ;
    vx[x] = vy[y] = vz[z] = 1;

    if(obj1isMin != dot(n, column(r2, y)) > 0)
    {
        if(obj1isMin != dot(n, column(r2, z)) > 0)
        {
            p3 = b2->getWorldPoint(-s2[x]/2*vx + s2[y]/2*vy + s2[z]/2*vz);
            p4 = b2->getWorldPoint(s2[x]/2*vx + s2[y]/2*vy + s2[z]/2*vz);
        }
        else
        {
            p3 = b2->getWorldPoint(-s2[x]/2*vx + s2[y]/2*vy - s2[z]/2*vz);
            p4 = b2->getWorldPoint(s2[x]/2*vx + s2[y]/2*vy - s2[z]/2*vz);
        }
    }
    else
    {
        if(obj1isMin != dot(n, column(r2, z)) > 0)
        {
            p3 = b2->getWorldPoint(-s2[x]/2*vx - s2[y]/2*vy + s2[z]/2*vz);
            p4 = b2->getWorldPoint(s2[x]/2*vx - s2[y]/2*vy + s2[z]/2*vz);
        }
        else
        {
            p3 = b2->getWorldPoint(-s2[x]/2*vx - s2[y]/2*vy - s2[z]/2*vz);
            p4 = b2->getWorldPoint(s2[x]/2*vx - s2[y]/2*vy - s2[z]/2*vz);
        }
    }

    
    vec3 A1 = p2 - p1;
    vec3 A2 = p4 - p3;
    vec2 C1(-dot(A1, A1), -dot(A1, A2));
    vec2 C2(dot(A1, A2), dot(A2, A2));
    vec2 B(dot((p1 - p3), A1), dot((p1 - p3), A2));
    float d = determinant(mat2(C1, C2));
    float t1 = determinant(mat2(B, C2)) / d;
    float t2 = determinant(mat2(C1, B)) / d;
    vec3 c = 0.5f * ((p1 + t1 * A1) + (p3 + t2 * A2));

    if(dot(n, b1->getPosition() - c) < 0)
        n = -n;

    vector<tuple<vec3,vec3>> p;
    p.push_back({make_tuple(c,n)});
    return p;
}

vector<tuple<vec3,vec3>> collisionPlane(const Box* b1, const Box* b2, int i, bool obj1isMin, vec3 n)
{
    vec3 s1 = b1->getSize();
    vec3 s2 = b2->getSize();
    mat3 r1 = mat3(b1->getRotationMatrix());
    mat3 r2 = mat3(b2->getRotationMatrix());

    int f = (obj1isMin == dot(n, column(r1, i)) > 0) ? 1 : -1 ;

    int x = i, y = (i+1)%3, z = (i+2)%3 ;
    vec3 vx(0), vy(0), vz(0);
    vx[x] = f ;
    vy[y] = vz[z] = 1;

    vec3 p1 = b1->getWorldPoint(s1[x]/2*vx + s1[y]/2*vy + s1[z]/2*vz);
    vec3 p2 = b1->getWorldPoint(s1[x]/2*vx - s1[y]/2*vy + s1[z]/2*vz);
    vec3 p3 = b1->getWorldPoint(s1[x]/2*vx + s1[y]/2*vy - s1[z]/2*vz);
    vec3 p4 = b1->getWorldPoint(s1[x]/2*vx - s1[y]/2*vy - s1[z]/2*vz);

    array<vec3,8> vertices = b2->getVertices() ;
    float extrem = dot(vertices[0], n);
    array<int,8> q = {0};
    int count = 1 ;
    for(int j = 1 ; j < 8 ; j++)
    {
        float d = dot(vertices[j], n) ;
        //Encore une fois pour les erreurs de projection.
        if(fabs(d - extrem) < 0.0001)
        {
            cout << fixed << setprecision(20) << d << endl ;
            q[count] = j ;
            count++;
        }
        else if((d < extrem) == obj1isMin)
        {
            cout << d << endl ;
            count = 1 ;
            extrem = d ;
            q[0] = j ;
        }
    }

    vector<tuple<vec3,vec3>> p;
    if(count == 1)
    {
        cout << "plan/point" << endl;
        vec3 po = vertices[q[0]] - 0.5f*(extrem-dot(p1,n))*n; ;
        p.push_back({make_tuple(po,n)});

    }

    else if(count == 2)
    {
        cout << "plan/arrete" << endl ;
    }
    else if(count == 4)
    {
        cout << "plan/plan" << endl ;
    }
    else
    {
        cout << "cout : " << count << " impossible..." << endl ; 
    }
    p.push_back({make_tuple(p1,n)});
    p.push_back({make_tuple(p2,n)});
    p.push_back({make_tuple(p3,n)});
    p.push_back({make_tuple(p4,n)});
    for(int i = 0 ; i < count ; i++)
    {
        p.push_back({make_tuple(vertices[q[i]],n)});
    }
    return p;
}
vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* obj1, const Box* obj2)
{
    mat3 r1 = mat3(obj1->getRotationMatrix());
    mat3 r2 = mat3(obj2->getRotationMatrix()); 

    //Normales de test (3 axes + 3 axes + produit vectoriel des axes 2 à 2)
    array<vec3,15> n ({column(r1,0),
            column(r1,1),
            column(r1,2),
            column(r2,0),
            column(r2,1),
            column(r2,2),
            cross(column(r1,0),column(r2,0)),
            cross(column(r1,0),column(r2,1)),
            cross(column(r1,0),column(r2,2)),
            cross(column(r1,1),column(r2,0)),
            cross(column(r1,1),column(r2,1)),
            cross(column(r1,1),column(r2,2)),
            cross(column(r1,2),column(r2,0)),
            cross(column(r1,2),column(r2,1)),
            cross(column(r1,2),column(r2,2))});

    bool obj1IsMin ;

    bool temp;
    int minIndex = 0;
    float minDepth = overlapDepth(obj1, obj2, n[0], obj1IsMin);

    for(int i = 1 ; i < 15 ; i++)
    {
        if(l1Norm(n[i]) != 0)
        {
            float depth = overlapDepth(obj1, obj2, n[i], temp) ;
            //Permet de compenser les erreurs avec les produits vectoriels.
            //Sinon la collision arrete/arrete est privilégiée lorsque les boite sont alignées.
            if(depth < minDepth - 0.001f)
            {
                minDepth = depth;
                minIndex = i;
                obj1IsMin = temp;
            }
        }

    }


    vec3 point ;
    if(minIndex < 3)
    {
        return collisionPlane(obj1, obj2, minIndex, obj1IsMin, n[minIndex]);
    }
    else if(minIndex < 6)
    {
        return collisionPlane(obj2, obj1, minIndex - 3, !obj1IsMin, n[minIndex]);
    }
    else
    {
        return collisionEdges(obj1, obj2, (minIndex-6)/3, (minIndex-6)%3, obj1IsMin, n[minIndex]);
    }
}

bool Collisions::collide(const Box* b, const Mesh* m)
{
    return false;
}

bool Collisions::collide(const Mesh* m, const Box* b)
{
    return collide(b, m);
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Box* b, const Mesh* m)
{
    return vector<tuple<vec3,vec3>>();
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* m, const Box* b)
{
    return vector<tuple<vec3,vec3>>();
}

bool Collisions::collide(const Mesh* obj1, const Mesh* obj2)
{
    return false;
}

vector<tuple<vec3,vec3>> Collisions::collisionPoints(const Mesh* obj1, const Mesh* obj2)
{
    return vector<tuple<vec3,vec3>>();
}
