// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "../misc/ArrayStruct.h"

using namespace OriGraphics;
struct SpriteDesc {
	Vector2 pos;
	float rotation;
	float scale;
	unsigned int states;
};
class GLInstancedSprites{
private:
	GLuint vertexbuffer;

	ArrayT<GLuint> textureIDs;
	ArrayStruct<SpriteDesc> spriteDesc;
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
