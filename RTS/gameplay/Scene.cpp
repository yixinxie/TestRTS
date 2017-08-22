#include "Scene.h"
#include "InputManager.h"
Scene::Scene() {

}
Scene::~Scene() {

}
void Scene::init(Renderer* _renderer) {
	renderer = _renderer;
	units.reserve();
	
}
void Scene::addOObject(OObject* obj) {
	OObjectArray.push(obj);
}
void Scene::initScene() {
	InputManager* inp = allocT<InputManager>();
	addOObject(inp);
}
void Scene::update(float timeElapsed) {
	for (int i = 0; i < OObjectArray.length; ++i) {
		OObjectArray[i]->update(timeElapsed);
	}
}
