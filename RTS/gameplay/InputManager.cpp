#include "InputManager.h"
#include "SelectorRect.h"
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
			IntVector2 currentPos;
			currentPos.x = mx;
			currentPos.y = my;
			OERenderer->mousePosToWorldSpace(currentPos, &mouseDownPos);
			
		}
		else {
			IntVector2 currentPos;
			Vector2 worldPos;
			currentPos.x = mx;
			currentPos.y = my;
			OERenderer->mousePosToWorldSpace(currentPos, &worldPos);
			
			rect->updateRectScale((worldPos - mouseDownPos) / 2.0f);
			rect->updateRectPos(mouseDownPos + (worldPos - mouseDownPos) / 2.0f);
			//rect->updateRectPos(mouseDownPos);
			//printf_s("%d %d\n", mx, my);
		}
	}
	else{
		rect->updateRectScale(Vector2::zero());
		leftButtonDown = false;
	}
}