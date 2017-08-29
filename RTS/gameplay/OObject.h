#pragma once
#include "../graphics/Renderer.h"
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
// 
class OObject {
private:
	char name[32];
	
public:
	OObject(void);
	virtual ~OObject();
	void setName(const char* str);
	const char* getName(void);
	
	virtual void update(float deltaTime) = 0;
};