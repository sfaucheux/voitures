#ifndef PObject_H
#define PObject_H

#include <string>
#include <list>
#include <vector>
#include <tuple>

#include "../geometry/geometry.h"
#include "../geometry/boundingsphere.h"
#include "../geometry/aabb.h"

#include "../glm/glm.hpp"

class Node;

class PBox;
class PMesh;
class PSphere;

class PObject
{
    public:
        PObject(Geometry& geo);
        virtual ~PObject();

        /*Accesseurs*/
		int getId() const;
        const glm::vec3 getPosition() const;
        const glm::vec3& getVelocity() const;
        const glm::vec3& getAcceleration() const;
        const glm::vec3 getRotation() const;
        const glm::vec3& getAngularVelocity() const;
        const glm::vec3& getAngularAcceleration() const;
        const glm::vec3& getForces() const;
        const glm::vec3& getTorques() const;
        const glm::mat3& getInertia() const;
        const glm::mat3& getInertiaInv() const;
        const Geometry& getGeometry() const;

        const AABB& getAABB() const;
        const BoundingSphere& getBoundingSphere() const;

        glm::vec3 getPointVelocity(const glm::vec3& point) const;
        glm::vec3 getPointForce(const glm::vec3& point) const;
        bool isStatic() const;
        float getMass() const;
        float getInertiaMomentum(const glm::vec3& axis) const;
        float getLinearDamping() const;
        float getAngularDamping() const;
        Node* getNode() const;

        /*Modificateurs*/
		void setId(int id);
        void setMass(float m);
        void setVelocity(glm::vec3 s);
        void setAcceleration(glm::vec3 a);
        void setAngularVelocity(glm::vec3 s);
        void setAngularAcceleration(glm::vec3 a);
        void setStatic(bool s);
        void setLinearImpulse(glm::vec3);
        void setAngularImpulse(glm::vec3);
        void setInertia(glm::mat3);
        void setNode(Node* node);

        void translate(glm::vec3 t);
        void rotate(glm::vec3 angle);

        void addForce(glm::vec3 f);
        void addTorque(glm::vec3 t);
        void addContact(std::tuple<PObject*, glm::vec3, glm::vec3> contact);
        void resetActions();


    private:
		
		int m_id;
        glm::vec3 m_position;
        glm::vec3 m_tempPosition;
        glm::vec3 m_rotation;
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;

        glm::vec3 m_angularVelocity;
        glm::vec3 m_angularAcceleration;

        float m_linearDamping;
        float m_angularDamping;

        bool m_awake;

        glm::vec3 m_forces;
        glm::vec3 m_torques;

        Geometry& m_geometry;
        BoundingSphere m_boundingSphere ;
        AABB m_AABB ;

        std::list<std::tuple<PObject*, glm::vec3, glm::vec3>> m_contacts;

        glm::mat3 m_inertia;
        glm::mat3 m_inertiaInv;
        float m_mass;
        bool m_static;
        Node* m_node;

};

#endif
