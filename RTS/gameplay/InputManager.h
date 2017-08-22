#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
class InputManager : public OObject {
private:
	// motion states
	Vector2 pos;
	float facing; // rotation
	float moveSpeed;
	float collisionRadius;

	// animation states

	byte animState; // idle, moving, attacking etc.
	int baseFrame;
	int frame;
public:
	InputManager(void);
	~InputManager();
	void init(void);
	void update(float deltaTime);
};