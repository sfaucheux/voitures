#ifndef PObject_H
#define PObject_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>


class PObject
{
    public:
    PObject();
    virtual void loadObject() = 0;

    void setMass(float m);
    void setSpeed(glm::vec3 s);
    void setAcceleration(glm::vec3 a);
    void setAngularSpeed(glm::vec3 s);
    void setAngularAcceleration(glm::vec3 a);
    void setStatic(bool s);

    void rotate(glm::vec3 axis, float  angle);
    void translate(glm::vec3 t);

    float getMass();
    glm::vec3 getSpeed();
    glm::vec3 getAcceleration();
    glm::vec3 getAngularSpeed();
    glm::vec3 getAngularAcceleration();
    bool isStatic();

    float getVolume();
        virtual ~PObject();

    private:
        glm::mat4 m_model;
        glm::mat3 m_inertia;
        glm::vec3 m_centroid;

        glm::vec3 m_acceleration;
        glm::vec3 m_speed;

        glm::vec3 m_angularSpeed;
        glm::vec3 m_angularAcceleration;

        float m_mass;
        float m_volume;
        bool m_static;
};

#endif
