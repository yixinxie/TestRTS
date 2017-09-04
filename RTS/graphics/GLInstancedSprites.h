// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
using namespace OriGraphics;
struct SpriteDesc {
	Vector2 pos;
	float rotation;
	Vector2 scale;
	Vector2 uv;
	//unsigned int states;
};
// primarily for ui atlas.
//struct SpriteSheetUV {
//	char name[32];
//	Vector2 left_bottom;
//	Vector2 right_top;
//};
/*
currently the class is instantiated multiple times.
vertex_buffer, shaders can be shared among the instances.
*/
class GLInstancedSprites{
private:
	GLuint vertex_buffer; // base vertex buffer
	GLuint instance_buffer; // per instance data and states.

	
	GLuint textureId;
	ArrayStruct<SpriteDesc> spriteDesc;
	int sprite_max; // number of sprite desc on gpu.
	GLuint samplerVarHnd;
	GLuint viewprojMatrixHnd;
	GLuint shaderHnd;
	GLuint initShaders(const char* vertex_file_path, const char* fragment_file_path);
	GLuint createTexture(unsigned int width, unsigned int height, const unsigned char* initialData);
public:
	GLInstancedSprites(void);
	// overrides
	void init(void);
	void onRender(glm::mat4 proj_view_mat);
	GLuint newSpriteSheet(const char* spritePath);
	int newSprite(Vector2 pos, Vector2 uv);
	void updateSprite(int spriteId, Vector2 pos);
	void updateSprite(int spriteId, Vector2 pos, float angle, Vector2 scale);
	
	void updateBufferFromSpriteDesc(void);
	void dispose(void);
	static void parseUVTxt(const char* content, ArrayStruct<SpriteSheetUV>& out);
};
