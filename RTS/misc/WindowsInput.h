#pragma once
#include "GLFW/glfw3.h"
#define INPUT_ARROW_UP GLFW_KEY_UP
#define INPUT_ARROW_DOWN GLFW_KEY_DOWN
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
};
