#pragma once
#include "../graphics/Renderer.h"
#include "../misc/ArrayT.h"

using namespace OriGraphics;
class Scene {
private:
	class Renderer* renderer;
	std::unordered_map<unsigned int, class OObject*> objectLookup;
	ArrayPtr<class OObject*> OObjectArray;
	ArrayPtr<class Unit*> units;

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
