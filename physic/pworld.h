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
        static const unsigned int MAX_OBJECTS = 2;
        static const unsigned int MIN_OBJECTS = 1;

        PWorld(glm::vec3 gravity);
        ~PWorld();

        void setGravity(glm::vec3 gravity);
		void update(float step);
		void addObject(PObject*);
		void updateObject(int);
		void translateObject(PObject* obj, glm::vec3 t);
		void removeObject(PObject*);

		const Node* getOctree() const;
		const PObject* getPObject(int id) const;

	private:
		void computeVelocities(float step);
		void computePositions(float step);
		void broadPhase();
		void narrowPhase();
		void positionsResponse();
		void velocitiesResponse();

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
		std::vector<std::array<int ,2>> m_potentialCollisions;
		std::vector<std::tuple<Contact*, int, int>> m_contacts ;
};

#endif
