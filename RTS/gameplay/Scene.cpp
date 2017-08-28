#include "Scene.h"
#include "SelectorRect.h"
#include "InputManager.h"
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
	

		//instancedSprites->newSprite(Vector2(0.5, 0), Vector2(7, 0));
		//instancedSprites->newSprite(Vector2(-0.5, -0.5), Vector2(1, 0));
		//instancedSprites->newSprite(Vector2(0.5, -0.5), Vector2(1, 0));
		//instancedSprites->newSprite(Vector2(-1.5, -0.5), Vector2(1, 0));
		//instancedSprites->newSprite(Vector2(-0.5, -1.5), Vector2(1, 0));


	
}
void Scene::addOObject(OObject* obj) {
	OObjectArray.push(obj);
}
void Scene::initScene() {
	G::instance()->currentScene = this;
	InputManager* inp = newClass<InputManager>("input manager");
	addOObject(inp);

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

	SelectorRect* rect = newClass<SelectorRect>();
	rect->init();
	OObjectArray.push(rect);
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