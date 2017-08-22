#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "../graphics/Renderer.h"
#include "Unit.h"
#include "OObject.h"
using namespace OriGraphics;
class Scene {
private:
	Renderer* renderer;
	ArrayT<OObject*> OObjectArray;
	//ArrayStruct<Unit> units;
public:
	Scene(void);
	~Scene();
	void init(Renderer* _renderer);
	void initScene(void);
	void update(float timeElapsed);
	void addOObject(OObject* obj);
};
