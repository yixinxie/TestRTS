#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/ArrayT.h"
// used for non-performance critical entities.
class OObject {
private:
	// change this for debug mode.
	char name[32];
	
public:
	OObject(void);
	virtual ~OObject();
	void setName(const char* str);
	const char* getName(void);
	
	virtual void update(float deltaTime);
};