#pragma once
#include "../misc/G.h"
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
	ArrayPtr<OObject*> OObjectArray;
	ArrayPtr<Unit*> units;
	void (*f)();
public:
	Scene(void);
	~Scene();
	void init(Renderer* _renderer);
	void initScene(void);
	void update(float timeElapsed);
	void addOObject(OObject* obj);
	void addUnit(Vector2 pos, Vector2 uv);
	//void setTimer(void);
};
