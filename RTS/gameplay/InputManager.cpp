#include "InputManager.h"
#include "SelectorRect.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
#include "Unit.h"
#include "Camera.h"
InputManager::InputManager() {
	leftButtonDown = false;
	setName("input_manager");
}
InputManager::~InputManager() {

}
void InputManager::init() {
	cam = (Camera*)OEScene->getOObjectByName("camera");
}
void InputManager::update(float deltaTime) {
	int mx, my;
	OEInput->mousePos(&mx, &my);
	IntVector2 currentPos;
	currentPos.x = mx;
	currentPos.y = my;
	if (rect == nullptr) {
		rect = (SelectorRect*) OEScene->getOObjectByName("selector_rect");
			return;
	}
	
	if (OEInput->mouseButton(0)){
		
		if (leftButtonDown == false)
		{
			// on mouse down
			leftButtonDown = true;
			
			OERenderer->mousePosToWorldSpace(currentPos, &mouseDownPos);
			
		}
		else {
			// on mouse drag
			Vector2 worldPos;
			OERenderer->mousePosToWorldSpace(currentPos, &worldPos);
			
			rect->updateRectScale((worldPos - mouseDownPos) / 2.0f);
			rect->updateRectPos(mouseDownPos + (worldPos - mouseDownPos) / 2.0f);
			//rect->updateRectPos(mouseDownPos);
			//printf_s("%d %d\n", mx, my);
		}
	}
	else{
		if (leftButtonDown)
		{
			rect->updateRectScale(Vector2::zero());
			leftButtonDown = false;

			Vector2 worldPos;
			OERenderer->mousePosToWorldSpace(currentPos, &worldPos);

			Vector2 min, max;
			ArrayPtr<Unit*> selected;
			min.x = min(mouseDownPos.x, worldPos.x);
			min.y = min(mouseDownPos.y, worldPos.y);
			max.x = max(mouseDownPos.x, worldPos.x);
			max.y = max(mouseDownPos.y, worldPos.y);

			OEScene->findUnitsByArea(min, max, selected);
			OEScene->setSelectedUnits(selected);
			printf_s("%d selected\n", selected.length);
		}
	}
	if (OEInput->mouseButton(1)) {
		Vector2 worldPos;
		OERenderer->mousePosToWorldSpace(currentPos, &worldPos);
		OEScene->orderMove(worldPos);
	}

	updateMouseScroll(deltaTime);
	updateCameraPosAdjustment(deltaTime);
}

void InputManager::updateCameraPosAdjustment(float deltaTime) {
	Vector2 adjustVec = Vector2::zero();
	if (OEInput->getKey(InputKeys::A)) {
		adjustVec.x = -1.0f;
	}
	else if (OEInput->getKey(InputKeys::D)) {
		adjustVec.x = 1.0f;
	}
	if (OEInput->getKey(InputKeys::W)) {
		adjustVec.y = 1.0f;
	}
	if (OEInput->getKey(InputKeys::S)) {
		adjustVec.y = -1.0f;
	}
	Vector2 camPos = cam->getPos();
	camPos += adjustVec * deltaTime * cameraMoveSpeed * cam->getSize();
	cam->setPos(camPos);
}

void InputManager::updateMouseScroll(float deltaTime) {
	float scrollValue = OEInput->getScrollValue();
	if (scrollValue != 0.0f) {

		float newSize = cam->getSize();
		newSize -= scrollValue;
		cam->setSize(newSize);
	}
}