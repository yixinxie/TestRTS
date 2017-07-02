// RTS.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "misc/BasicMem.h"
#include "misc/G.h"
#include "misc/CharHelper.h"
#include "graphics/Renderer.h"
#include "graphics/GLManager.h"
BasicMemory basicMem;
using namespace OriGraphics;
G* g;

int main()
{
	basicMem.initHeap(1000000);
	G::instance()->renderer = new GLManager();
	G::instance()->renderer->init(0, 1024, 768);
	
	/* Loop until the user closes the window */
	GLFWwindow* wnd = ((GLManager*)G::instance()->renderer)->window;
	while (!glfwWindowShouldClose(wnd))
	{
		G::instance()->renderer->render();
		Sleep(16);
	}
	G::instance()->renderer->dispose();
	
	return 0;

}
