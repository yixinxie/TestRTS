#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
class b2World;
class StaticCollision : public OObject {
private:
	b2World* box2DInst;
public:
	StaticCollision(void);
	~StaticCollision();
	void init(void);
	virtual void update(float deltaTime) override;
};