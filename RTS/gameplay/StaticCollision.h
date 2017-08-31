#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"

class StaticCollision : public OObject {
private:

public:
	StaticCollision(void);
	~StaticCollision();
	void init(void);
	void update(float deltaTime);
};