#ifndef PObject_H
#define PObject_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <list>


class PObject
{
    enum type {Dynamic, Kinematic, Static} ;
    public:
        PObject();
        virtual void loadObject() = 0;

        void setMass(float m);
        void setVelocity(glm::vec3 s);
        void setAcceleration(glm::vec3 a);
        void setAngularVelocity(glm::vec3 s);
        void setAngularAcceleration(glm::vec3 a);
        void setStatic(bool s);

        void rotate(glm::vec3 angle);
        void translate(glm::vec3 t);

        float getMass();
        glm::vec3 getVelocity();
        glm::vec3 getAcceleration();
        glm::vec3 getAngularVelocity();
        glm::vec3 getAngularAcceleration();
        bool isStatic();

        float getVolume();
        virtual ~PObject();

    private:

        type m_type ;
        glm::vec3 m_position;
        glm::vec3 m_angle;
        glm::mat3 m_inertia;
        glm::vec3 m_centroid;

        glm::vec3 m_acceleration;
        glm::vec3 m_velocity;

        glm::vec3 m_angularVelocity;
        glm::vec3 m_angularAcceleration;

        float m_linearDamping ;
        float m_angularDamping ;

        float m_mass;
        float m_volume;
        bool m_static;
        bool m_awake ;
/*
        std::list<Fixture> m_fixtures ;
        std::list<Joint> m_joints ;
        */
};

#endif
