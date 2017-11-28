#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/ArrayT.h"
#include "OObject.h"

class SelectorRect : public OObject {
private:
	bool leftButtonDown; // selecting
	Vector2 pos;
	Vector2 scale;
	int textureId;
	int spriteId;

public:
	SelectorRect(void);
	~SelectorRect();
	void init(void);
	virtual void update(float deltaTime) override;
	void updateRectScale(Vector2 scale);
	void updateRectPos(Vector2 pos);
};