#pragma once
#include <vector>
#include <Windows.h>
#include "../misc/ArrayT.h"
#include "../misc/SimpleVector.h"

class RecastManager;

enum UnitAnimStates : byte{
	Idle,
	Moving,
	Attacking,
};
class Unit {
protected:
	// motion states
	Vector2 pos;
	float facing; // rotation
	float moveSpeed;
	float collisionRadius;

	Vector2 targetPos;

	// animation states

	UnitAnimStates animState; // idle, moving, attacking etc.
	int baseFrame;
	int textureId;
	int spriteDescId;
	int frame;

	// pathfinding
	RecastManager* recast;
	Vector2 pathPoints[32];

public:
	Unit(void);
	~Unit();
	void init(Vector2 pos, const char* id);
	void update(float deltaTime);
	const Vector2& getPos(void) const;
	void setMoveTarget(const Vector2& _targetPos);
};