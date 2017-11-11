#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "../misc/G.h"

WindowsInput::WindowsInput()
{
}

WindowsInput::~WindowsInput()
{
}

void WindowsInput::setGLFWHandle(GLFWwindow* _window) {
	glfwWindow = _window;

	glfwSetScrollCallback(_window, &scrollCallback);
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

void WindowsInput::scrollCallback(GLFWwindow* _window, double xoffset, double yoffset)
{
	//printf_s("%f %f\n", xoffset, yoffset);
	OEInput->scrollValue = yoffset;
}

float WindowsInput::getScrollValue() const {
	return scrollValue;
}

void WindowsInput::resetEvents(){
	//if (canReset) {
	scrollValue = 0.0f;
	canReset = false;
	//}
}

void WindowsInput::markReset() {
	canReset = true;

}