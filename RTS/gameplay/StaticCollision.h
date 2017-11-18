#pragma once
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
#include "Box2D/Box2D.h"
class b2World;
class RTSRaycastCallback;
class StaticCollision : public OObject {
private:
	b2World* box2DInst;
public:
	StaticCollision(void);
	~StaticCollision();
	void init(void);
	//virtual void update(float deltaTime) override;
	b2Body* addAgent(Vector2 pos);
	void updateAgent(b2Body*, Vector2 pos);
	bool raycast(Vector2 from, Vector2 to, RTSRaycastCallback* result);
};

class RTSRaycastCallback : public b2RayCastCallback {
public:
	bool hit;
	b2Fixture* fixture;
	b2Vec2 point;
	b2Vec2 normal;
	float32 fraction;
	RTSRaycastCallback() {
		hit = false;
		fixture = nullptr;
	}

	virtual float32 ReportFixture(
		b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction) override;
};