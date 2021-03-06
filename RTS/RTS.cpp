// RTS.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include <string>
#include <chrono>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "misc/BasicMem.h"
#include "misc/G.h"
#include "misc/CharHelper.h"
#include "graphics/Renderer.h"
#include "graphics/GLManager.h"
#include "gameplay/Scene.h"
#include "misc/WindowsInput.h"
BasicMemory basicMem;
using namespace OriGraphics;
G* g;
using namespace std::chrono;
int main()
{
	Scene* test;
	basicMem.initHeap(1024 * 1024 * 32);
	G::instance()->renderer = newClass<GLManager>();
	G::instance()->renderer->init(0, 1024, 768);
	
	/* Loop until the user closes the window */
	GLFWwindow* wnd = ((GLManager*)G::instance()->renderer)->window;
	G::instance()->input = newClass<WindowsInput>("input");
	G::instance()->input->setGLFWHandle(wnd);

	test = newClass<Scene>("scene");
	test->init(G::instance()->renderer);
	test->initScene();
	high_resolution_clock::time_point fps0 = high_resolution_clock::now();
	int32 frames = 0;
	float avgtime = 0.0f;
	while (!glfwWindowShouldClose(wnd))
	{
		high_resolution_clock::time_point before = high_resolution_clock::now();
		glfwPollEvents();
		test->update(0.0167f);
		G::instance()->renderer->render();
		G::instance()->input->resetEvents();
		
		high_resolution_clock::time_point after = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(after - before);
		double sleepFor = 0.016667 - time_span.count();
		avgtime += time_span.count();
		if (sleepFor > 0.0) {

			Sleep((int32)(sleepFor * 1000));
		}
		time_span = duration_cast<duration<double>>(after - fps0);
		frames++;
		if (time_span.count() >= 1.0) {
			avgtime /= frames;
			//printf_s("FPS: %d\n", frames);
			printf_s("avg frame time: %fms (%d)\n", avgtime * 1000, frames);
			fps0 = high_resolution_clock::now();
			frames = 0;
		}
	}
	deallocT(test);
	deallocT(G::instance()->input);
	G::instance()->renderer->dispose();
	deallocT(G::instance()->renderer);
	basicMem.report();
	getchar();
	return 0;
}
