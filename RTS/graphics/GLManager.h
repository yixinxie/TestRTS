// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLInstancedSprites.h"
#include "GLIMLines.h"
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
	//void prepareViewProjectionCB(ID3D11Buffer** constantBuffer, const Vector3 position, const Vector3 euler, float fieldOfView, float aspectRatio, float nearPlane, float farPlane, ID3D11Buffer** constantBuffer2);
	void assembleDrawables(void);
	void restoreRenderTarget(void);

public:
	GLManager(void);
	~GLManager();
	// overrides
	bool init(HWND hWnd, int _width, int _height);
	void render(void);

	void line2D(Vector2 pos0, Vector2 pos1, Color color);
	int newSpriteSheet(const char* spritePath);
	int newSprite(int handle, Vector2 pos, Vector2 uv);
	void updateSprite(int textureId, int spriteId, Vector2 uv);
	void updateSprite(int textureId, int spriteId, Vector2 pos, float angle, Vector2 scale);
	
};
