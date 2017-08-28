#include "InputManager.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
InputManager::InputManager() {
	leftButtonDown = false;
}
InputManager::~InputManager() {

}
void InputManager::init() {

}
void InputManager::update(float deltaTime) {
	if (OEInput->mouseButton(0)){
		printf_s("pressed");
		leftButtonDown = true;
		G::instance()->currentScene->addUnit(Vector2(2, 2), Vector2(1, 0));
	}
	else{
		leftButtonDown = false;
	}
}