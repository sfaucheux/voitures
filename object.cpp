#include <cmath>

#include "object.h"
#include "graphics/gbox.h"
#include "graphics/gsphere.h"

using namespace std ;
using namespace glm ;

Object::Object(Sphere s)
{
    m_geom = new Sphere(s);
    float radius = s.getRadius();
    m_gObj = new gSphere(*(Sphere*)m_geom);
    m_pObj = new PObject(*(Sphere*)m_geom);
    m_pObj->setInertia(mat3(2*m_pObj->getMass()*radius*radius/5.));
}

Object::Object(Box b)
{
    m_geom = new Box(b);
    float w = b.getWidth(), h = b.getHeight(), d = b.getDepth();
    m_gObj = new gBox(*(Box*)m_geom);
    m_pObj = new PObject(*(Box*)m_geom);
    mat3 inertia(0);
    inertia[0][0] = m_pObj->getMass()*(h*h + d*d)/12.;
    inertia[1][1] = m_pObj->getMass()*(w*w + d*d)/12.;
    inertia[2][2] = m_pObj->getMass()*(h*h + w*w)/12.;
    m_pObj->setInertia(inertia);
}

Object::Object(Mesh m)
{
    m_geom = new Mesh(m);
    m_gObj = new Drawable(*(Mesh*)m_geom);
    m_gObj->load(m.getVertices(), m.getIndices());
    m_pObj = new PObject(*(Mesh*)m_geom);
}

Object::~Object()
{
    delete m_pObj;
    delete m_gObj;
    delete m_geom;
}

PObject* Object::getPObject() const
{
    return m_pObj;
}

Drawable* Object::getDrawable() const
{
    return m_gObj;
}

const Geometry* Object::getGeometry() const
{
    return m_geom;
}

void Object::translate(glm::vec3 t)
{
    m_geom->translate(t);
}

void Object::rotate(glm::vec3 r)
{
    m_geom->rotate(r);
}
