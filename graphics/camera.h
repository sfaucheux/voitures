#ifndef Camera_H
#define Camera_H

#include "../glm/glm.hpp"

class Camera
{
    public:
        Camera(glm::vec3 pos, glm::vec3 tar, glm::vec3 up);
        ~Camera();

        void setPosition(glm::vec3 pos);
        void setUp(glm::vec3 up);
        void setTarget(glm::vec3 tar);
        void setOrientation(double x, double y);
        void move(glm::vec3 dep, float time);
        void update();

        glm::mat4 getView() const;
        glm::vec3 getPosition() const;
        glm::vec3 getOrientation() const;
        glm::vec3 getUp() const;
        glm::vec3 getTarget() const;
        glm::vec3 getLeft() const;


    private:
        glm::vec3 m_position;
        glm::vec3 m_orientation;
        glm::vec3 m_target;
        glm::vec3 m_forward;
        glm::vec3 m_up;
        glm::vec3 m_left;

        double m_theta, m_phi;

        glm::mat4 m_view;

        glm::mat3 m_passage ;
        glm::mat3 m_passageInverse ;

        void updateMatrix();
        void updateAngles();

};

#endif
