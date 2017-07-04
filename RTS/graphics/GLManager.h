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

using namespace OriGraphics;
class GLManager : public Renderer{
public:
	GLFWwindow* window;
	glm::mat4 proj_view;
private:
	GLInstancedSprites* instancedSprites;
	void initDepthStencil(void);
	void prepareCamera(void);
	//void prepareViewProjectionCB(ID3D11Buffer** constantBuffer, const Vector3 position, const Vector3 euler, float fieldOfView, float aspectRatio, float nearPlane, float farPlane, ID3D11Buffer** constantBuffer2);
	void assembleDrawables(void);
	void restoreRenderTarget(void);
	GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
public:
	GLManager(void);
	// overrides
	bool init(HWND hWnd, int _width, int _height);
	void dispose(void);
	
	void initInstancing(void);
	void disposeInstancing(void);
	void platformRender(void);

	// experimental
	void renderWithShadowMap(void);
	void renderWithoutShadowMap(void);

	void newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath);
	void newSprite(const Vector2 pos, const Vector2 uv);
};