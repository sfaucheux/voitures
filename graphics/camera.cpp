#include "../glm/gtx/transform.hpp"

#include "camera.h"

using namespace glm;

Camera::Camera(vec3 pos, vec3 tar, vec3 up) : m_position(pos), m_up(normalize(up))
{
	setTarget(tar);
	update();
}

Camera::~Camera()
{
}

void Camera::updateMatrix()
{
	m_passage = mat3(m_forward, m_left, m_up);
	m_passageInverse = inverse(m_passage);
}

void Camera::updateAngles()
{
	vec3 m_vect = m_passageInverse * m_orientation;
	m_phi = asin(m_vect.z);
	m_theta = asin(m_vect.y / cos(m_phi));
}

void Camera::setPosition(glm::vec3 pos)
{
	m_position = pos;
	m_target = m_position + m_orientation;
	update();
}

void Camera::setUp(glm::vec3 up)
{
	m_up = normalize(up);
	m_left = normalize(cross(m_up, m_forward));
	m_forward = normalize(cross(m_left, m_up));

	updateMatrix();
	setOrientation(0, 0);
	update();
}

void Camera::setTarget(glm::vec3 tar)
{
	m_orientation = normalize(tar - m_position);
	m_left = normalize(cross(m_up, m_orientation));
	m_forward = normalize(cross(m_left, m_up));

	updateMatrix();
	updateAngles();
}

void Camera::setOrientation(double x, double y)
{
	m_theta += -x * 0.002f;
	m_phi += -y * 0.002f;

	double limite = 1.55;
	if (m_phi > limite)
		m_phi = limite;
	else if (m_phi < - limite)
		m_phi = -limite;

	vec3 m_vect = m_passage * m_orientation;

	m_vect.x = cos(m_phi) * cos(m_theta);
	m_vect.y = cos(m_phi) * sin(m_theta);
	m_vect.z = sin(m_phi);

	m_orientation = m_passageInverse * m_vect;
	m_left = normalize(cross(m_up, m_orientation));

	m_target = m_position + m_orientation;

	update();
}

void Camera::move(vec3 mvt, float time)
{
	if (mvt != vec3(0, 0, 0))
	{
		mvt = normalize(mvt) * time * 100.f;
		setPosition(m_position + m_orientation * mvt.x + m_left * mvt.y + normalize(cross(m_orientation, m_left)) * mvt.z);
		update();
	}
}

void Camera::update()
{
	m_view = lookAt(m_position, m_target, m_up);
}

mat4 Camera::getView() const
{
	return m_view ;
}

vec3 Camera::getPosition() const
{
	return m_position;
}

glm::vec3 Camera::getOrientation() const
{
	return m_orientation;
}

glm::vec3 Camera::getUp() const
{
	return m_up;
}

glm::vec3 Camera::getTarget() const
{
	return m_target;
}

glm::vec3 Camera::getLeft() const
{
	return m_left;
}
