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
	Vector2 rotation_scale;
	Vector2 uv;
	
	//unsigned int states;
};

class GLInstancedSprites{
private:
	GLuint vertex_buffer; // base vertex buffer
	GLuint instance_buffer; // per instance data and states.

	
	GLuint textureId;
	SpriteDesc* spriteDesc;
	int sprite_count;
	int sprite_max;
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
	GLuint newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath);
	int newSprite(const Vector2 pos, const Vector2 uv);
	void updateSprite(int spriteId, const Vector2 pos);
	void updateBufferFromSpriteDesc(void);
	void dispose(void);
	void useTexture(const char* resourceId, unsigned int _width, unsigned int _height);
};
