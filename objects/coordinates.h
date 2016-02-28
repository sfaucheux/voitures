#ifndef Coordinates_H
#define Coordinates_H

#include "../glm/glm.hpp"

class Coordinates
{
    public:
        Coordinates();
        Coordinates(glm::vec3 pos);
        Coordinates(glm::vec3 pos, glm::vec3 rot);
        virtual ~Coordinates();

        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::mat4& getModel();

        void translate(glm::vec3 translation);
        void rotate(glm::vec3 rotation);
        void homothetie(glm::vec3 homoth);


    private:
        glm::mat4 m_model;
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_homoth;

};

#endif
