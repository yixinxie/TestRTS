#pragma once
#include "../graphics/Renderer.h"
#include "../misc/ArrayT.h"

class Unit;
class OObject;

using namespace OriGraphics;
class Scene {
private:
	class Renderer* renderer;
	std::unordered_map<unsigned int, OObject*> objectLookup;
	ArrayPtr<OObject*> OObjectArray;
	ArrayPtr<Unit*> units;
	ArrayPtr<Unit*> selectedUnits;

	void (*f)();
public:
	Scene(void);
	~Scene();
	void init(Renderer* _renderer);
	void initScene(void);
	void update(float timeElapsed);
	void addOObject(OObject* obj);
	OObject* getOObjectByName(const char* name);
	Unit* addUnit(Vector2 pos, const char* id);
	void findUnitsByArea(Vector2 min, Vector2 max, ArrayPtr<Unit*>& units);
	void setSelectedUnits(ArrayPtr<Unit*>& units);
	void orderMove(const Vector2& targetPos);
};
