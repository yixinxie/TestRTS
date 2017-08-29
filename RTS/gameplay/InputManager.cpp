#include "InputManager.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
InputManager::InputManager() {
	leftButtonDown = false;
	setName("input_manager");
}
InputManager::~InputManager() {

}
void InputManager::init() {

}
void InputManager::update(float deltaTime) {
	if (rect == nullptr) {
		rect = (SelectorRect*) OEScene->getOObjectByName("selector_rect");
			return;
	}
	
	if (OEInput->mouseButton(0)){
		int mx, my;
		OEInput->mousePos(&mx, &my);
		if (leftButtonDown == false)
		{
			leftButtonDown = true;
			
			mouseDownPos.x = mx;
			mouseDownPos.y = my;
		}
		else {
			Vector2 currentPos;
			currentPos.x = mx;
			currentPos.y = my;
			rect->updateRectScale(currentPos - mouseDownPos);
		}
	}
	else{
		leftButtonDown = false;
	}
}