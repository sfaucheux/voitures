#include <cmath>

#include "../glm/glm.hpp"

#include "sphere.h"
#include "../physic/psphere.h"

#define GET_INDEX(i, j) ((i) * (nbPoints / 2) + (j))

Sphere::Sphere(float radius)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;

    static const int nbPointsUnitSphere = 20;
    int nbPoints = radius * nbPointsUnitSphere;
    float dAngle = 2.0 * M_PI / (float)nbPoints;
    int topVertexIndex = nbPoints * (nbPoints / 2);

    for (int i = 0; i < nbPoints; i++) {
        for (int j = 0; j < nbPoints / 2; j++) {
            float theta = i * dAngle;
            float phi = j * dAngle - (M_PI / 2.0);
            vertices.push_back(glm::vec3(radius * cos(theta) * cos(phi), radius * sin(theta) * cos(phi), radius * sin(phi)));
            int nextI = (i < nbPoints - 1) ? i + 1 : 0;
            int a = GET_INDEX(i, j);
            int b = GET_INDEX(nextI, j);
            int nextJ = (j < (nbPoints / 2) - 1) ? j + 1 : j;
            int c = (j == nextJ) ? topVertexIndex : GET_INDEX(i, nextJ);
            int d = (j == nextJ) ? topVertexIndex : GET_INDEX(nextI, nextJ);
            indices.push_back(glm::uvec3(a, b, c));
            indices.push_back(glm::uvec3(b, d, c));
        }
    }
    vertices.push_back(glm::vec3(0, 0, radius));

    m_gObj.load(vertices, indices);
    m_pObj = new PSphere(radius);
}

Sphere::~Sphere()
{
    delete m_pObj;
}

Object::ObjectType Sphere::getType()
{
    return Object::Sphere;
}
