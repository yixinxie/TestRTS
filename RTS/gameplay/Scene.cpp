#include "Scene.h"
#include "SelectorRect.h"
#include "InputManager.h"
#include "Terrain.h"
#include "StaticCollision.h"
#include "RVOManager.h"
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
	InputManager* inp = newClass<InputManager>("input manager");
	addOObject(inp);

	SelectorRect* rect = newClass<SelectorRect>();
	rect->init();
	addOObject(rect);

	Terrain* terrain = newClass<Terrain>();
	terrain->init();
	addOObject(terrain);

	StaticCollision* staticCollision = newClass<StaticCollision>();
	staticCollision->init();
	addOObject(staticCollision);

	RVOManager* rvo = newClass<RVOManager>();
	rvo->init();
	addOObject(rvo);

	Unit* newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(0.5, 0), Vector2(7, 0));
	units.push(newUnit);

	newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(-0.5, -0.5), Vector2(1, 0));
	units.push(newUnit);

	newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(0.5, -0.5), Vector2(1, 0));
	units.push(newUnit);

	newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(-1.5, 0.5), Vector2(1, 0));
	units.push(newUnit);

	newUnit = newClass<Unit>("units");
	newUnit->init(Vector2(-0.5, -1.5), Vector2(1, 0));
	units.push(newUnit);
}
void Scene::update(float timeElapsed) {
	for (int i = 0; i < OObjectArray.length; ++i) {
		OObjectArray[i]->update(timeElapsed);
	}
	for (int i = 0; i < units.length; ++i) {
		units[i]->update(timeElapsed);
	}
}
void Scene::addUnit(Vector2 pos, Vector2 uv){
	Unit* newUnit = newClass<Unit>("units");
	newUnit->init(pos, uv);
	units.push(newUnit);
}