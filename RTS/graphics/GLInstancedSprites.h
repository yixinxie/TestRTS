// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"


using namespace OriGraphics;
class GLInstancedSprites{
public:
	GLFWwindow* window;
private:
	GLuint vertexbuffer;
	GLuint textureID;
	GLuint samplerVarHnd;
	GLuint shaderHnd;
	GLuint initShaders(const char* vertex_file_path, const char* fragment_file_path);
	int createTexture(unsigned int width, unsigned int height, const unsigned char* initialData);
public:
	GLInstancedSprites(void);
	// overrides
	void init(void);
	void onRender(void);
	void newSprite(unsigned int width, unsigned int height, const char* spritePath);
	void dispose(void);
};