#include "StaticCollision.h"
#include "misc/G.h"
#include "misc/WindowsInput.h"
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

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = box2DInst->CreateBody(&myBodyDef);

	//shape definition
	b2EdgeShape polygonShape;
	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	//add four walls to the static body
	b2Vec2 bl(-20, 0);
	b2Vec2 br(20, 0);
	b2Vec2 tl(-20, 40);
	b2Vec2 tr(20, 40);
	polygonShape.Set(bl, br); //ground
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.Set(tl, tr);//ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.Set(bl, tl);//left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.Set(br, tr);//right wall
	staticBody->CreateFixture(&myFixtureDef);

	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 20);
	//polygonShape.Set(2, 2);
	myFixtureDef.density = 1;
	for (int i = 0; i < 5; i++)
		box2DInst->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

	//circles
	b2CircleShape circleShape;
	circleShape.m_radius = 2;
	myFixtureDef.shape = &circleShape;
	for (int i = 0; i < 5; i++)
		box2DInst->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

	//turn gravity off
	box2DInst->SetGravity(b2Vec2(0, 0));
}
void StaticCollision::update(float deltaTime) {
	box2DInst->Step(deltaTime, 1, 1);
}