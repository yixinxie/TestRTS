#include "Scene.h"
#include "../misc/SimpleVector.h"
#include "../graphics/Renderer.h"
#include "Unit.h"
#include "misc/G.h"
#include "OObject.h"
#include "SelectorRect.h"
#include "InputManager.h"
#include "Terrain.h"
//#include "StaticCollision.h"
#include "RecastManager.h"
#include "Camera.h"
#include "AABBManager.h"

Scene::Scene(void) {

}

Scene::~Scene() {
	for (int i = 0; i < OObjectArray.length; ++i) {
		deallocT(OObjectArray[i]);
	}
	for (int i = 0; i < units.length; ++i) {
		deallocT(units[i]);
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

	AABBManager* aabb = newClass<AABBManager>();
	aabb->init();
	addOObject(aabb);

	Terrain* terrain = newClass<Terrain>();
	terrain->init();
	addOObject(terrain);

	//RVOManager* rvo = newClass<RVOManager>();
	//rvo->init();
	//addOObject(rvo);
	RecastManager* recastManager = newClass<RecastManager>("recast");
	recastManager->init();
	addOObject(recastManager);

	addUnit(Vector2(0, 0), "green");

	addUnit(Vector2(2, 0), "yellow");

	addUnit(Vector2(4, 0), "red");

	addUnit(Vector2(6, 0), "blue");

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
		units[i]->update(timeElapsed);
	}
}

void Scene::addUnit(Vector2 pos, const char* id){
	Unit* newUnit = newClass<Unit>("units");
	newUnit->init(pos, id);
	units.push(newUnit);
}

void Scene::findUnitsByArea(Vector2 min, Vector2 max, ArrayPtr<Unit*>& outUnits){
	for (int i = 0; i < units.length; ++i) {
		const Vector2& unitPos = units[i]->getPos();
		if (unitPos.x > min.x && unitPos.y > min.y &&
			unitPos.x < max.x && unitPos.y < max.y) {
			outUnits.push(units[i]);
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
	for (int i = 0; i < selectedUnits.length; ++i) {
		selectedUnits[i]->setMoveTarget(targetPos);
	}
}