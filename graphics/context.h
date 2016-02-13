#ifndef Context_H
#define Context_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

class Context
{
    public:
        Context(Renderer &renderer);
        virtual ~Context();

        static void errorCallback(int error, const char* description);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
        static void windowSizeCallback(GLFWwindow* window, int width, int height);
        void cursor(double xpos, double ypos);
        void key(int key, int scancode, int action, int mods);
        void windowSize(int width, int height);

        bool init(int width, int height, std::string title, int MSAA = 0);
        bool eventLoop();
        void clean();
        void show();

        double getFrametime();
        bool keyIsPressed(int key);


    private:
        void processEvents();
        GLFWwindow* m_window;
        Renderer &m_renderer;

        double m_xCursor, m_yCursor;
        double m_oldTime, m_frameTime;

};

#endif
