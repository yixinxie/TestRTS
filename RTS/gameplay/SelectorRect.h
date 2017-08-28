#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
class SelectorRect : public OObject {
private:
	bool leftButtonDown; // selecting
public:
	SelectorRect(void);
	~SelectorRect();
	void init(void);
	void update(float deltaTime);
};