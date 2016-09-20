#ifndef PWorld_H
#define PWorld_H

#include <list>
#include <array>
#include <set>
#include <tuple>
#include <stack>

#include "../glm/glm.hpp"

#include "pobject.h"
#include "node.h"
#include "../collision/contact.h"

class PWorld 
{
    public:
        //MAX >= MIN
        static const unsigned int MAX_OBJECTS = 6;
        static const unsigned int MIN_OBJECTS = 6;

        PWorld(glm::vec3 gravity);
        ~PWorld();

        void setGravity(glm::vec3 gravity);
        void update(float step);
        void addObject(PObject*);
        void updateObject(int);
        void translateObject(PObject* obj, glm::vec3 t);
        void removeObject(PObject*);

        const Node& getOctree() const;


    private:
        void integrate(float step);
        void broadPhase();
        void narrowPhase();
        void collisionResponse();
        glm::vec3 computeImpulse(PObject* obj1, PObject* obj2, glm::vec3 point, glm::vec3 normal);

        void addObject(Node* n, int object);
        void addObjectToChildren(Node* node, int object);
        void addObjectOutsideWorld(int object);
        void removeObject(Node* node, int object);
        void updateRoot();
        void updateNodeSubdivision(Node* node);
        void updateNodeMerge(Node* node);

        std::vector<PObject*> m_objects;
        std::vector<Node*> m_parents;
        Node* m_root;
        glm::vec3 m_gravity;
        std::vector<std::array<PObject*,2>> m_potentialCollisions;
        std::vector<std::tuple<Contact*, PObject*, PObject*>> m_contacts ;
};

#endif
