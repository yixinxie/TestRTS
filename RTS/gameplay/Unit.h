#pragma once
#include <vector>
#include <Windows.h>
#include "../misc/ArrayT.h"
#include "../misc/SimpleVector.h"

class AABBManager;
class RecastManager;
class StaticCollision;
class b2Body;
enum UnitAnimStates : byte{
	Idle,
	Moving,
	Attacking,
	MakingSpace,
};
class Unit {
protected:
	// motion states
	Vector2 lastPos;
	Vector2 pos;
	float facing; // rotation
	float collisionRadius;
	float speed;

	Vector2 targetPos;

	// animation states

	UnitAnimStates animState; // idle, moving, attacking etc.
	int baseFrame;
	int textureId;
	int spriteDescId;
	int frame;

	// pathfinding
	AABBManager* aabb;
	int32 aabbId;

	RecastManager* recast;
	int32 pathCount;
	int32 pathPointIndex;
	Vector2 pathPoints[32]; // reference path
	StaticCollision* phys;
	b2Body* b2body;

	Vector2 updateMovement(Vector2 desiredVelocity);
	void makeSpace(Vector2 _dir);

public:
	int dbgid;
	Unit(void);
	~Unit();
	void init(Vector2 pos, const char* id);
	void update(float deltaTime);
	const Vector2& getPos(void) const;
	void setMoveTarget(const Vector2& _targetPos);
};