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
		// screen width and height
		int width;
		int height;

		// while in window mode, the renderable area is slightly smaller than the area the window occupies.
		int windowWidth;
		int windowHeight;

		//vector<CameraDesc*> cameras;

		//int objectIndexIncrementer;
		//std::unordered_map<int, ObjectTransformDesc*> instancedObjects;

		//int spriteIndexIncrementer;
		//std::unordered_map<int, ObjectRectTransformDesc*> spriteObjects;

		//int lightIndexIncrementer;
		//std::unordered_map<int, LightSourceDesc*> lightSources;

		void updateRectTransforms(int idx, int parentLeft, int parentBottom, int parentRight, int parentTop);
		virtual void preRender(void);
		virtual void postRender(void);
	public:
		Renderer();
		virtual ~Renderer();
		virtual bool init(HWND hwnd, int _width, int _height) = 0;
		virtual void dispose(void);
		inline int getPixelWidth(void) { return width; }
		inline int getPixelHeight(void) { return height; }
		
		void render(void);
		virtual void platformRender(void) = 0;

		virtual void addLine2D(Vector2 pos0, Vector2 pos1, unsigned int color) = 0;
		//virtual int createTexture(unsigned int w, unsigned int h, const unsigned char* initialData) = 0;
		/*void setMainCamera(const Vector3& pos, const Vector3& rot, const float fov, const float _nearPlane, const float _farPlane);
		void updateMainCamera(const Vector3& pos, const Vector3& rot);
		int registerInstancedObject(void);
		void updateInstancedObject(const int id, const Vector3& position, const Vector3& rotation, const Vector3& scale);

		int registerLightSource(void);
		void updateLightSource(const int id, const Vector3& position, const Vector3& rotation);

		int registerSpriteObject(void);
		void updateSpriteObjectParent(const int id, const int parentId);
		void updateSpriteObject(const int id, RectTransform* rect);*/
		

		virtual int newSpriteSheet(unsigned int width, unsigned int height, const char* spritePath) = 0;
		virtual int newSprite(int handle, const Vector2 pos, const Vector2 uv) = 0;
		virtual void updateSprite(int textureId, int spriteId, const Vector2 uv) = 0;
	};
}
