#include "StaticCollision.h"
#include "misc/G.h"
//
#include "Box2D/Box2D.h"
StaticCollision::StaticCollision() {
	setName("static_collision");
}
StaticCollision::~StaticCollision() {
	delete box2DInst;
}
void StaticCollision::init() {
	//a static body
	//b2World* box2DInst = new b2World(gravity, doSleep);
	box2DInst = new b2World();
	box2DInst->SetAllowSleeping(true);
	box2DInst->SetGravity(b2Vec2(0.0f, 0.0f));

	/*b2BodyDef testBodyDef;
	testBodyDef.type = b2_kinematicBody;
	testBodyDef.position.Set(0, 0);
	b2Body* kinBody = box2DInst->CreateBody(&testBodyDef);

	b2CircleShape circle;
	circle.m_radius = 1.0f;
	circle.m_p = b2Vec2(0.0f, 0.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &circle;
	boxFixtureDef.density = 1;
	kinBody->CreateFixture(&boxFixtureDef);
	kinBody->SetTransform(b2Vec2(0, 0.9f), 0.0f);*/
	
	/*RTSRaycastCallback cb;
	box2DInst->RayCast(&cb, b2Vec2(-2.0f, 0.0f), b2Vec2(2.0f, 0.0f));
	int sdf = 0;*/
	////fixture definition
	//b2FixtureDef myFixtureDef;
	//myFixtureDef.shape = &polygonShape;

	////add four walls to the static body
	//b2Vec2 bl(-20, 0);
	//b2Vec2 br(20, 0);
	//b2Vec2 tl(-20, 40);
	//b2Vec2 tr(20, 40);
	//polygonShape.Set(bl, br); //ground
	//staticBody->CreateFixture(&myFixtureDef);
	//polygonShape.Set(tl, tr);//ceiling
	//staticBody->CreateFixture(&myFixtureDef);
	//polygonShape.Set(bl, tl);//left wall
	//staticBody->CreateFixture(&myFixtureDef);
	//polygonShape.Set(br, tr);//right wall
	//staticBody->CreateFixture(&myFixtureDef);

	//myBodyDef.type = b2_dynamicBody;
	//myBodyDef.position.Set(0, 20);
	////polygonShape.Set(2, 2);
	//myFixtureDef.density = 1;
	//for (int i = 0; i < 5; i++)
	//	box2DInst->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

	//circles
	/*b2CircleShape circleShape;
	circleShape.m_radius = 2;
	myFixtureDef.shape = &circleShape;
	for (int i = 0; i < 5; i++)
		box2DInst->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);*/
}

b2Body* StaticCollision::addAgent(Vector2 pos, void* userData){
	b2BodyDef agentBodyDef;
	agentBodyDef.type = b2_kinematicBody;
	agentBodyDef.position.Set(pos.x, pos.y);
	b2Body* kinBody = box2DInst->CreateBody(&agentBodyDef);

	b2CircleShape circle;
	circle.m_radius = 1.0f;
	circle.m_p = b2Vec2(0.0f, 0.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &circle;
	boxFixtureDef.density = 1;
	boxFixtureDef.userData = userData;
	kinBody->CreateFixture(&boxFixtureDef);
	return kinBody;
}
void StaticCollision::addStatic(Vector2 _pos, Vector2 _size) {
	b2BodyDef agentBodyDef;
	agentBodyDef.type = b2_staticBody;
	agentBodyDef.position.Set(_pos.x, _pos.y);
	b2Body* kinBody = box2DInst->CreateBody(&agentBodyDef);

	
	b2PolygonShape rect;
	rect.SetAsBox(_size.x, _size.y);


	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &rect;
	boxFixtureDef.density = 1;
	boxFixtureDef.userData = nullptr;
	kinBody->CreateFixture(&boxFixtureDef);
}

void StaticCollision::updateAgent(b2Body* b2body, Vector2 pos){
	b2body->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
}

bool StaticCollision::raycast(Vector2 from, Vector2 to, RTSRaycastCallback* result) {
	box2DInst->RayCast(result, b2Vec2(from.x, from.y), b2Vec2(to.x, to.y));
	return result->hit;
}

int StaticCollision::overlap(Vector2 center, float radius, b2QueryCallback* result) {
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(center.x - radius, center.y - radius);
	aabb.upperBound = b2Vec2(center.x + radius, center.y + radius);
	box2DInst->QueryAABB(result, aabb);
	return result->count;
}
//void StaticCollision::update(float deltaTime) {
	//box2DInst->Step(deltaTime, 1, 1);
//}

float32 RTSRaycastCallback::ReportFixture(b2Fixture* _fixture, const b2Vec2& _point,
	const b2Vec2& _normal, float32 _fraction){
	hit = true;
	userData = _fixture->GetUserData();
	point = _point;
	normal = _normal;
	fraction = _fraction;

	return 0.0f;
}