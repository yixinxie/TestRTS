#pragma once
#include "../graphics/Renderer.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
#include "../misc/ArrayT.h"
#include "OObject.h"
#include "rvo/RVO.h"
class RVO::RVOSimulator;
class RVOManager : public OObject {
private:
	RVO::RVOSimulator* sim;
	std::vector<RVO::Vector2> goals;
public:
	RVOManager(void);
	~RVOManager();
	void init(void);
	void update(float deltaTime);
};