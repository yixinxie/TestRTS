// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "misc/ArrayT.h"
#include "../graphics/Renderer.h"
class GLInstancedSprites;
class GLIMLines;
using namespace OriGraphics;
struct TextureMeta {
	GLuint textureId;
	int refCount;
};

class GLManager : public Renderer{
public:
	GLFWwindow* window;
	
private:
	glm::mat4 proj_view;
	int textureIdCounter;

	// char hash, index in instancedSprites
	std::unordered_map<unsigned int, int> textureIds;

	ArrayPtr<GLInstancedSprites*> instancedSprites;
	GLIMLines* debugRender;

	void initDepthStencil(void);
	void prepareCamera(void);
	void assembleDrawables(void);
	void restoreRenderTarget(void);

public:
	GLManager(void);
	~GLManager();
	// overrides
	bool init(HWND hWnd, int _width, int _height);
	void render(void);

	int newSpriteSheet(const char* spritePath);
	int newSprite(int handle, Vector2 pos, Vector2 uv);
	int newSprite(int handle, Vector2 pos, const char* id);
	
	void updateSprite(int textureId, int spriteId, Vector2 pos);
	void updateSprite(int textureId, int spriteId, Vector2 pos, float angle);
	void updateSprite(int textureId, int spriteId, Vector2 pos, float angle, Vector2 scale);
	
	// debug utility functions
	void line2D(Vector2 pos0, Vector2 pos1, Color color);
	void circle(Vector2 pos0, float radius, Color color);
};
