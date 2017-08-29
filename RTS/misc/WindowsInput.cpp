#include "WindowsInput.h"
#include "GLFW/glfw3.h"


WindowsInput::WindowsInput()
{
}


WindowsInput::~WindowsInput()
{
}
void WindowsInput::setGLFWHandle(GLFWwindow* _window) {
	glfwWindow = _window;
}

bool WindowsInput::getKey(int key){
	return glfwGetKey(glfwWindow, key) == GLFW_PRESS;
}
void WindowsInput::mousePos(int* x, int* y) {
	double doubleX;
	double doubleY;
	glfwGetCursorPos(glfwWindow, &doubleX, &doubleY);
	*x = doubleX;
	*y = doubleY;
}
bool WindowsInput::mouseButton(int idx) {
	return glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT + idx) == GLFW_PRESS;
}
