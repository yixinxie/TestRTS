#include "Scene.h"
#include "../misc/SimpleVector.h"
#include "../graphics/Renderer.h"
#include "Unit.h"
#include "misc/G.h"
#include "OObject.h"
#include "SelectorRect.h"
#include "InputManager.h"
#include "Terrain.h"
#include "StaticCollision.h"
#include "RecastManager.h"
#include "Camera.h"
#include "AABBManager.h"
#include "PathList.h"

Scene::Scene(void) : units(512){
}

Scene::~Scene() {
	//for (int i = 0; i < units.length; ++i) {
	//	deallocT(units[i]);
	//}
	for (int i = 0; i < OObjectArray.length; ++i) {
		deallocT(OObjectArray[i]);
	}
}

void Scene::init(Renderer* _renderer) {
	renderer = _renderer;
}

void Scene::addOObject(OObject* obj) {
	const char* objName = obj->getName();
	if (objName[0] != 0) {
		unsigned int key = CharHelper::charHash(obj->getName());
		if (objectLookup.find(key) != objectLookup.end()) {
			// duplicate key found!
			assert(false);
		}
		else {
			objectLookup.insert(std::pair<unsigned int, OObject*>(key, obj));
		}
	}
	OObjectArray.push(obj);
}

OObject* Scene::getOObjectByName(const char* name) {
	unsigned int key = CharHelper::charHash(name);
	if (objectLookup.find(key) != objectLookup.end()) {
		return objectLookup[key];
	}
	return nullptr;
}

void Scene::initScene() {
	G::instance()->currentScene = this;

	Camera* camera = newClass<Camera>("camera");
	camera->init();
	addOObject(camera);

	InputManager* inp = newClass<InputManager>("input manager");
	inp->init();
	addOObject(inp);

	SelectorRect* rect = newClass<SelectorRect>();
	rect->init();
	addOObject(rect);

	//AABBManager* aabb = newClass<AABBManager>();
	//aabb->init();
	//addOObject(aabb);
	StaticCollision* rvo = newClass<StaticCollision>("b2");
	rvo->init();
	addOObject(rvo);

	Terrain* terrain = newClass<Terrain>();
	terrain->init();
	addOObject(terrain);

	RecastManager* recastManager = newClass<RecastManager>("recast");
	recastManager->init();
	addOObject(recastManager);

	pathList = newClass<PathList>("path_List");
	pathList->init();
	addOObject(pathList);

	/*Unit* one = addUnit(Vector2(0, 0), "green");
	one->dbgid = 0;

	one = addUnit(Vector2(2, 0), "yellow");
	one->dbgid = 1;

	one = addUnit(Vector2(4, 0), "red");
	one->dbgid = 2;

	one = addUnit(Vector2(6, 0), "blue");
	one->dbgid = 3;*/
	const float spacing = 2.01f;
	int w_count = 32;
	int h_count = 16;
	//int w_count = 2;
	//int h_count = 2;
	int st = 2;
	for (int y = 0; y < h_count; ++y) {
		for (int x = 0; x < w_count; ++x) {
			Unit* one = addUnit(Vector2((st + x ) * spacing, (st + y) * spacing), "blue");
			one->dbgid = x + y * w_count;
		}
	}

	/*newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(0.5, -0.5), "blue");
	units.push(newUnit);

	*/
}

void Scene::update(float timeElapsed) {
	for (int i = 0; i < OObjectArray.length; ++i) {
		OObjectArray[i]->update(timeElapsed);
	}
	for (int i = 0; i < units.length; ++i) {
		units[i].update(timeElapsed);
	}
	for (int i = 0; i < units.length; ++i) {
		units[i].dirtyUpdate();
	}
}

Unit* Scene::addUnit(Vector2 pos, const char* id){
	Unit placeHolder;

	units.push(placeHolder);
	Unit* newUnit = &units[units.length - 1];
	newUnit->init(pos, id);
	return newUnit;
}

void Scene::findUnitsByArea(Vector2 min, Vector2 max, ArrayPtr<Unit*>& outUnits){
	for (int i = 0; i < units.length; ++i) {
		const Vector2& unitPos = units[i].getPos();
		if (unitPos.x > min.x && unitPos.y > min.y &&
			unitPos.x < max.x && unitPos.y < max.y) {
			outUnits.push(&units[i]);
		}
	}
}

void Scene::setSelectedUnits(ArrayPtr<Unit*>& _units){
	selectedUnits.clear();
	for (int i = 0; i < _units.length; ++i) {
		selectedUnits.push(_units[i]);
	}
}

void Scene::orderMove(const Vector2& targetPos) {
	// tentatively we just use the geometric center
	Vector2 center = Vector2::zero();
	int unitCount = selectedUnits.length;
	for (int i = 0; i < selectedUnits.length; ++i) {
		center += selectedUnits[i]->getPos();
	}
	center.x /= unitCount;
	center.y /= unitCount;
	
	int pathidx = pathList->newPath(center, targetPos, unitCount);
	if (pathidx >= 0) {
		for (int i = 0; i < selectedUnits.length; ++i) {
			selectedUnits[i]->setRefPath(pathidx);
		}
	}

	/*for (int i = 0; i < selectedUnits.length; ++i) {
		selectedUnits[i]->setMoveTarget(targetPos);
	}*/
}