#include "context.h"

using namespace std;
using namespace glm;

Context::Context(Renderer &renderer) : m_renderer(renderer), m_xCursor(0), m_yCursor(0), m_oldTime(glfwGetTime())
{
	glfwSetErrorCallback(Context::errorCallback);
}

Context::~Context()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Context::init(int width, int height, std::string title, int MSAA)
{
	if (!glfwInit())
		return false;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	glfwWindowHint(GLFW_SAMPLES, MSAA);
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetCursorPosCallback(m_window, cursorCallback);
	glfwSetWindowSizeCallback(m_window, windowSizeCallback);

    glewExperimental=true;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	return true;
}

bool Context::eventLoop()
{
	m_frameTime = glfwGetTime() - m_oldTime;
	m_oldTime = glfwGetTime();

	processEvents();

	return !glfwWindowShouldClose(m_window);

}

void  Context::cursor(double xpos, double ypos)
{
	double dx = xpos - m_xCursor;
	double dy = ypos - m_yCursor;
	m_xCursor = xpos;
	m_yCursor = ypos;
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		m_renderer.getCamera().setOrientation(-dx, -dy);
	}

}

void Context::errorCallback(int error, const char* description)
{
	cerr << description;
}

void Context::key(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Context::clean()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::show()
{
	glfwSwapBuffers(m_window);
}

double Context::getFrametime()
{
	return m_frameTime;
}

void Context::processEvents()
{
	glfwPollEvents();

	vec3 mvt(0);
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		mvt.x++;
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		mvt.x--;
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		mvt.y++;
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		mvt.y--;
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		mvt.z++;
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		mvt.z--;
	m_renderer.getCamera().move(mvt, m_frameTime);
}

void Context::windowSizeCallback(GLFWwindow *window, int width, int height)
{
    ((Context*)glfwGetWindowUserPointer(window))->windowSize(width, height);
}

void Context::windowSize(int width, int height)
{
    glViewport(0, 0, width, height);
    m_renderer.setPerspective(70.0, ((float)(width)) / height, 0.01, 1000);
}

void Context::cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	((Context*)glfwGetWindowUserPointer(window))->cursor(xpos, ypos);
}

void Context::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	((Context*)glfwGetWindowUserPointer(window))->key(key, scancode, action, mods);
}
