// include the basic windows header files and the Direct3D header files
#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "GLInstancedSprites.h"

using namespace OriGraphics;
class GLManager : public Renderer{
public:
	GLFWwindow* window;
private:
	GLuint vertexbuffer;
	GLuint textureID;
	GLuint samplerVarHnd;
	//ID3D11RenderTargetView* backbuffer;

	//D3D11_VIEWPORT viewport;

	//// depth and stencil
	//ID3D11Texture2D* depthStencilTex;
	//ID3D11DepthStencilState* depthStencilState;
	//ID3D11DepthStencilView* depthStencilView;

	//// instancing
	//ID3D11Buffer* viewProjMatrixCB;

	//// techniques:
	//DXInstancedSprite* instancedSprites;
	//DXInstancing* instancedQuads;
	//
	//DXInstancedMesh* instancedMesh;
	//DXShadowMap* shadowMap;
	//DXDeferred* deferredShading;

	// resources
	//

	void initDepthStencil(void);
	void prepareCamera(void);
	//void prepareViewProjectionCB(ID3D11Buffer** constantBuffer, const Vector3 position, const Vector3 euler, float fieldOfView, float aspectRatio, float nearPlane, float farPlane, ID3D11Buffer** constantBuffer2);
	void assembleDrawables(void);
	void restoreRenderTarget(void);
	GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void loadPNG(const IntVector2& _dim, const char* fileName);
public:
	GLManager(void);
	// overrides
	bool init(HWND hWnd, int _width, int _height);
	virtual void dispose(void);
	int createTexture(unsigned int width, unsigned int height, const unsigned char* initialData);
	
	void initInstancing(void);
	void disposeInstancing(void);
	void platformRender(void);

	// experimental
	void renderWithShadowMap(void);
	void renderWithoutShadowMap(void);
};