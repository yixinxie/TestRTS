#pragma once
#include "../misc/ArrayT.h"
#include "OObject.h"
#include "Box2D/Box2D.h"
class b2World;
class StaticCollision : public OObject {
private:
	b2World* box2DInst;
public:
	StaticCollision(void);
	~StaticCollision();
	void init(void);
	virtual void update(float deltaTime) override;
	b2Body* addAgent(Vector2 pos, void* userData);
	void updateAgent(b2Body*, Vector2 pos);
	bool raycast(Vector2 from, Vector2 to, b2RayCastCallback* result);
	int overlap(Vector2 center, float radius, b2QueryCallback* result);
	int overlapRect(Vector2 min, Vector2 max, b2QueryCallback* result);
	void addStatic(Vector2 _pos, Vector2 _size);
};

//class RTSRaycastCallback : public b2RayCastCallback {
//public:
//	bool hit;
//	void* userData;
//	b2Vec2 point;
//	b2Vec2 normal;
//	float32 fraction;
//	RTSRaycastCallback() {
//		hit = false;
//		userData = nullptr;
//	}
//
//	virtual float32 ReportFixture(
//		b2Fixture* fixture, const b2Vec2& point,
//		const b2Vec2& normal, float32 fraction) override;
//};