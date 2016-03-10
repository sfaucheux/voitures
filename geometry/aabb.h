#ifndef AABB_H
#define AABB_H

#include "../glm/glm.hpp"

class AABB
{
    public:
        AABB(glm::vec3 size, glm::vec3 position = glm::vec3(0));
        glm::vec3 getPosition() const;
        glm::vec3 getSize() const;
        float getBottomPosition() const;
        float getTopPosition() const;
        float getLeftPosition() const;
        float getRightPosition() const;
        float getFrontPosition() const;
        float getBackPosition() const;

    private:
        glm::vec3 m_size;
        glm::vec3 m_position;
};

#endif
