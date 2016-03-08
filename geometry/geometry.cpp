#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/norm.hpp"
#include "../glm/gtx/euler_angles.hpp"

#include "geometry.h"

using namespace glm;

Geometry::Geometry() : m_pos(vec3(0, 0, 0)), m_rot(vec3(0, 0, 0)), m_model(1.0), m_modelInv(1.0)
{
}

Geometry::~Geometry()
{
}

glm::vec3 Geometry::getPosition() const
{
    return m_pos;
}

glm::vec3 Geometry::getRotation() const
{
    return m_rot;
}

mat4 const& Geometry::getModel() const
{
    return m_model;
}

void Geometry::updateModel()
{
    m_model = glm::translate(mat4(1), m_pos);
    float norm = l2Norm(m_rot);
    if (norm != 0)
        m_model = glm::rotate(m_model, norm, m_rot);
    m_modelInv = glm::inverse(m_model);
    //m_modelInv = glm::rotate(mat4(1), -norm, m_rot);
    //m_modelInv = glm::translate(m_modelInv, -m_pos);
}

void Geometry::translate(vec3 translation)
{
    m_pos += translation;
    updateModel();
}

void Geometry::rotate(vec3 rotation)
{
    m_rot += rotation;
    updateModel();
}

vec3 Geometry::getLocalPoint(const vec3& point) const
{
   return vec3(m_modelInv*vec4(point,1));
}
