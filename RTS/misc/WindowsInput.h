#pragma once
#include "GLFW/glfw3.h"
class WindowsInput
{
protected:
	GLFWwindow* glfwWindow;
	static void scrollCallback(GLFWwindow* _window, double xoffset, double yoffset);
	bool canReset;
	float scrollValue;

public:
	WindowsInput();
	~WindowsInput();
	void setGLFWHandle(GLFWwindow* _window);
	bool getKey(int key);
	void mousePos(int* x, int* y);
	bool mouseButton(int idx);
	float getScrollValue() const;
	void markReset();
	void resetEvents();
};

enum InputKeys {
	arrowUp = GLFW_KEY_UP,
	arrowDown = GLFW_KEY_DOWN,

	W = GLFW_KEY_W,
	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D,

};
