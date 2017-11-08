#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
class SelectorRect;
class InputManager : public OObject {
private:
	bool leftButtonDown; // selecting
	Vector2 mouseDownPos;
	SelectorRect* rect;
public:
	InputManager(void);
	~InputManager();
	void init(void);
	void update(float deltaTime);
};