#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
// 
class OObject {
private:
public:
	OObject(void);
	virtual void update(float deltaTime) = 0;
	void constructor(void);
	void destructor(void);
};