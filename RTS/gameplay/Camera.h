#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"

class Camera : public OObject {
protected:
	Vector2 pos;
	float size;
public:
	Camera(void);
	~Camera();
	void init(void);
	void update(float deltaTime);
	void setSize(float size);
	float getSize() const;
	Vector2 getPos() const;
	void setPos(Vector2 pos);
};