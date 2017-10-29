#pragma once
#include "../graphics/Renderer.h"
#include "../misc/ArrayT.h"
// 
class Unit {
private:
	// motion states
	Vector2 pos;
	float facing; // rotation
	float moveSpeed;
	float collisionRadius;

	// animation states

	byte animState; // idle, moving, attacking etc.
	int baseFrame;
	int textureId;
	int spriteDescId;
	int frame;
public:
	Unit(void);
	~Unit();
	void init(Vector2 pos, Vector2 uv);
	void update(float deltaTime);
};