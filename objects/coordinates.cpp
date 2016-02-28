#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/euler_angles.hpp"

#include "coordinates.h"

using namespace glm;

Coordinates::Coordinates() : m_pos(vec3(0, 0, 0)), m_rot(vec3(0, 0, 0)), m_homoth(vec3(1.0, 1.0, 1.0))
{
}

Coordinates::Coordinates(vec3 pos) : m_pos(pos), m_rot(vec3(0, 0, 0)), m_homoth(vec3(1.0, 1.0, 1.0))
{
}

Coordinates::Coordinates(vec3 pos, vec3 rot) : m_pos(pos), m_rot(rot), m_homoth(vec3(1.0, 1.0, 1.0))
{
}

Coordinates::~Coordinates()
{
}

glm::vec3 Coordinates::getPosition()
{
    return m_pos;
}

glm::vec3 Coordinates::getRotation()
{
    return m_rot;
}

mat4& Coordinates::getModel()
{
    m_model = eulerAngleYXZ(m_rot.y, m_rot.x, m_rot.z);
    m_model = glm::translate(m_model, m_pos);
    m_model = glm::scale(m_model, m_homoth);
    return m_model;
}

void Coordinates::translate(vec3 translation)
{
    m_pos += translation;
}

void Coordinates::rotate(vec3 rotation)
{
    m_rot += rotation;
}

void Coordinates::homothetie(vec3 homoth)
{
    m_homoth += homoth;
}
