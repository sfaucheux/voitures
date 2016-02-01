#ifdef PObject_H
#define PObject_H

#include "glm/glm.hpp"
#include <string>

class PObject
{
    public:
        virtual PObject() = 0;
        virtual loadObject();
        void setMass(float m);
        float getMass();
        float getVolume();
        virtual ~PObject();

    private:
        glm::mat3 m_inertiaMat;
        glm::vec3 m_centroid;
        float m_mass;
        float m_volume;
        bool m_static;
};

#endif
