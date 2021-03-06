#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
// the rendering of terrain.
class Terrain : public OObject {
private:
	Vector2 pos;
	Vector2 scale;
	int textureId;
	int spriteId;
	byte* grid;
public:
	const int32 dim = 256;
	Terrain(void);
	~Terrain();
	void init(void);
	/*void updateRectScale(Vector2 scale);
	void updateRectPos(Vector2 pos);*/
};