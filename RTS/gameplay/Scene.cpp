#include "Scene.h"
#include "InputManager.h"
Scene::Scene(void) {

}
Scene::~Scene() {
	for (int i = 0; i < OObjectArray.length; ++i) {
		deallocT(OObjectArray[i]);
	}
}
void Scene::init(Renderer* _renderer) {
	renderer = _renderer;
	//units.reserve();
	
}
void Scene::addOObject(OObject* obj) {
	OObjectArray.push(obj);
}
void Scene::initScene() {
	InputManager* inp = alloc<InputManager>();
	callCons(inp);
	addOObject(inp);
}
void Scene::update(float timeElapsed) {
	for (int i = 0; i < OObjectArray.length; ++i) {
		OObjectArray[i]->update(timeElapsed);
	}
}
