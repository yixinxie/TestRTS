#pragma once
#include "../graphics/Renderer.h"
#include "../misc/WindowsInput.h"
#include "../gameplay/Scene.h"
#define OERenderer G::instance()->renderer
#define OEInput G::instance()->input
#define OEScene G::instance()->currentScene

/* Ori Engine */
using namespace OriGraphics;
// G is the global variable holder.
class Scene;
class G{
private:
	G(void);
	static G* _instance;
public:
	static G* instance(void);
	Renderer* renderer;
	WindowsInput* input;
	Scene* currentScene;
};