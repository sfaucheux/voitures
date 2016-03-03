#ifndef PObject_H
#define PObject_H

#include <string>
#include <list>
#include <vector>
#include <tuple>

#include "../geometry/geometry.h"
#include "../glm/glm.hpp"

class PBox;
class PMesh;
class PSphere;

class PObject
{
    public:
        PObject(Geometry& geo);
        virtual ~PObject();

        /*Accesseurs*/
        const glm::vec3& getPosition() const ;
        const glm::vec3& getVelocity() const ;
        const glm::vec3& getAcceleration() const ;
        const glm::vec3& getRotation() const ;
        const glm::vec3& getAngularVelocity() const ;
        const glm::vec3& getAngularAcceleration() const ;
        const glm::vec3& getForces() const ;
        const glm::vec3& getTorques() const ;
        const glm::mat3& getInertia() const ;
        const glm::mat3& getInertiaInv() const ;
        const glm::mat4& getModel() const ;
        const Geometry& getGeometry() const ;

        glm::vec3 getLocalPoint(const glm::vec3& point) const ;
        glm::vec3 getPointVelocity(const glm::vec3& point) const ;
        glm::vec3 getPointForce(const glm::vec3& point) const ;
        bool isStatic() const ;
        float getMass() const ;
        float getInertiaMomentum(const glm::vec3& axis) const ;
        float getLinearDamping() const ;
        float getAngularDamping() const ;

        /*Modificateurs*/
        void setMass(float m);
        void setVelocity(glm::vec3 s);
        void setAcceleration(glm::vec3 a);
        void setAngularVelocity(glm::vec3 s);
        void setAngularAcceleration(glm::vec3 a);
        void setStatic(bool s);
        void setLinearImpulse(glm::vec3);
        void setAngularImpulse(glm::vec3);
        void setInertia(glm::mat3);

        void rotate(glm::vec3 angle);
        void translate(glm::vec3 t);
        void addForce(glm::vec3 f);
        void addTorque(glm::vec3 t);
        void addContact(std::tuple<PObject*, glm::vec3, glm::vec3> contact);
        void resetActions();


    protected:


        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;

        glm::vec3 m_angularVelocity;
        glm::vec3 m_angularAcceleration;

        float m_linearDamping;
        float m_angularDamping;

        bool m_awake;

        glm::vec3 m_forces;
        glm::vec3 m_torques;

        Geometry& m_geometry ;
        
        std::list<std::tuple<PObject*, glm::vec3, glm::vec3>> m_contacts;

        //Masqué aussi pour les classes filles
    private:
        void updateMatrices();

        glm::mat4 m_model;
        glm::mat4 m_modelInv;
        glm::vec3 m_position;
        glm::vec3 m_angle;
        glm::mat3 m_inertia;
        glm::mat3 m_inertiaInv;
        float m_mass;
        bool m_static;

};

#endif
