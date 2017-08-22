#include "InputManager.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
InputManager::InputManager() {
	printf_s("ipmancons");
}
InputManager::~InputManager() {

}
void InputManager::init() {

}
void InputManager::update(float deltaTime) {
	if (OEInput->mouseButton(0)){
		printf_s("pressed");

	}
	if (OEInput->getKey(InputKeys::arrowDown)) {
		printf_s("pressed");

	}
}