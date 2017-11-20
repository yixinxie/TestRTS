#pragma once
#include "graphics/Renderer.h"
#include "gameplay/Scene.h"
#include "misc/WindowsInput.h"
#define OERenderer G::instance()->renderer
#define OEInput G::instance()->input
#define OEScene G::instance()->currentScene

/* Ori Engine */
using namespace OriGraphics;
// G is the global variable holder.
class G{
private:
	G(void);
	static G* _instance;
public:
	static G* instance(void);
	class Renderer* renderer;
	class WindowsInput* input;
	class Scene* currentScene;
};