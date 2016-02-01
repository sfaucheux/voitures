#ifdef PWorld_H
#define PWorld_H

#include <list>
#include "glm/glm.hpp"

class PWorld 
{
    public:
        PWorld();
        void setGravity(float gravity);
        void update();
        void addObject(PObject&);
        void removeObject(PObject&);

    private:
        std::list<PObject> m_objects ;
        glm::vec3 m_gravity ;


};
#endif
