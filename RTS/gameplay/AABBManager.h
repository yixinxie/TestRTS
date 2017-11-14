#pragma once
#include "../misc/ArrayT.h"
#include "../plugins/aabbcc/AABB.h"
#include "OObject.h"
using namespace aabb;
class AABBManager : public OObject {
protected:
	Tree aabbTree;
	int32 currentAgentIndex;
public:
	AABBManager();
	~AABBManager();
	void init();

	int32 addAgent(Vector2 _pos, float _radius);
	void updateAgent(int32 idx, Vector2 _pos, float _radius);
	void query(Vector2 _pos, float _radius);
};
