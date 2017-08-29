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
	std::unordered_map<unsigned int, OObject*> objectLookup;
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
	OObject* getOObjectByName(const char* name);
	void addUnit(Vector2 pos, Vector2 uv);
	//void setTimer(void);
};
