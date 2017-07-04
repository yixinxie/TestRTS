#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "../graphics/Renderer.h"
#include "Unit.h"
using namespace OriGraphics;
class Scene {
private:
	Renderer* renderer;
	ArrayStruct<Unit> units;
public:
	Scene(void);
	~Scene();
	void init(Renderer* _renderer);
	void update(float timeElapsed);
};