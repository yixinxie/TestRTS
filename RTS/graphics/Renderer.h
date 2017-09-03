#pragma once
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <unordered_map>
//#include "CameraDesc.h"
//#include "LightSourceDesc.h"
//#include "ObjectTransformDesc.h"
#include "../misc/SimpleVector.h"
using namespace std;
namespace OriGraphics{

	/* 
	the Renderer class serves as an intermediary class between the graphics APIs(directx,
	opengl etc) and the entity component system. It manages the states of all rendering-related objects.

	*/
	class Renderer{
	protected:
		// screen width and height, or buffer width/height
		int width;
		int height;

		// while in window mode, the renderable area is slightly smaller than the area the window occupies.
		int windowWidth;
		int windowHeight;

		Vector2 cameraPos;
		float cameraSize; // orthogonal Size

	public:
		Renderer();
		virtual ~Renderer();
		virtual bool init(HWND hwnd, int _width, int _height) = 0;
		virtual void dispose(void);
		inline int getPixelWidth(void) { return width; }
		inline int getPixelHeight(void) { return height; }
		
		virtual void render(void) = 0;

		virtual void line2D(Vector2 pos0, Vector2 pos1, Color color) = 0;

		virtual int newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath) = 0;
		virtual int newSprite(int handle, Vector2 pos, Vector2 uv) = 0;
		virtual void updateSprite(int textureId, int spriteId, Vector2 uv) = 0;
		virtual void updateSprite(int textureId, int spriteId, Vector2 pos, float angle, Vector2 scale) = 0;
		virtual void updateCamera(Vector2 pos, float size);

		void mousePosToWorldSpace(const IntVector2& pos, Vector2* posWorldSpace);
	};
}
