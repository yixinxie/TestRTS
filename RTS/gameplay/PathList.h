#pragma once
#include "../misc/ArrayT.h"
#include "OObject.h"
struct PathInfo {
	static const int MaxPathCount = 32;
	int32 pathCount;
	int32 pathPointIndex;
	Vector2 pathPoints[MaxPathCount]; // reference path
	Vector2 pathTurnPointNormals[MaxPathCount];
	int32 refCount;
};
class RecastManager;
class PathList : public OObject {
private:
	

	RecastManager* recast;
public:
	ArrayStruct<PathInfo> paths;
	
	PathList(void);
	~PathList();
	void init(void);

	int newPath(Vector2 fromPos, Vector2 toPos, int refCount);
	virtual void update(float deltaTime) override;
	void finishPath(int pathidx);
};
