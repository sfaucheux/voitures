#ifndef PObject_H
#define PObject_H

#include <string>
#include <list>

#include "../glm/glm.hpp"

class PBox;
class PMesh;
class PSphere;

class PObject
{
    enum type {Dynamic, Kinematic, Static} ;
    public:
    PObject();
    virtual ~PObject();

    //Fonctions de collision précises, le type de retour int n'est que temporaire,
    //le plus adapté serait une structure ou un objet avec (point, normale, distance d'interpénétration).

    //fonction qui renvoit la collision d'un pobject quelconque avec soit même.
    virtual int collide(PObject* obj) = 0 ;

    //collision avec tous les autres pobjects.
    virtual int collideWithBox(PBox* obj) = 0 ;
    virtual int collideWithMesh(PMesh* obj) = 0 ;
    virtual int collideWithSphere(PSphere* obj) = 0 ;

    void setMass(float m);
    void setVelocity(glm::vec3 s);
    void setAcceleration(glm::vec3 a);
    void setAngularVelocity(glm::vec3 s);
    void setAngularAcceleration(glm::vec3 a);
    void setStatic(bool s);

    glm::vec3 getPosition();
    glm::vec3 getVelocity();
    glm::vec3 getAcceleration();
    glm::vec3 getRotation();
    glm::vec3 getAngularVelocity();
    glm::vec3 getAngularAcceleration();
    glm::vec3 getForces();
    glm::vec3 getTorques();
    float getMass();
    glm::mat3 getInertia();
    float getLinearDamping();
    float getAngularDamping();
    bool isStatic();

    float getVolume();

    void rotate(glm::vec3 angle);
    void translate(glm::vec3 t);
        void addForce(glm::vec3 f);
        void addTorque(glm::vec3 t);
        void resetActions();


    protected:

        type m_type ;
        glm::vec3 m_position;
        glm::vec3 m_angle;
        glm::mat3 m_inertia;
        glm::vec3 m_centroid;

        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;

        glm::vec3 m_angularVelocity;
        glm::vec3 m_angularAcceleration;

        float m_linearDamping ;
        float m_angularDamping ;

        float m_mass;
        float m_volume;
        bool m_static;
        bool m_awake ;

        glm::vec3 m_forces ;
        glm::vec3 m_torques ;
/*
        std::list<Fixture> m_fixtures ;
        std::list<Joint> m_joints ;
        */

};

#endif
