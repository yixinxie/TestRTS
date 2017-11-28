#include "PathList.h"
#include "RecastManager.h"
#include "misc/G.h"

//
PathList::PathList() {
	setName("path_list");
}
PathList::~PathList() {
}
void PathList::init() {
	recast = (RecastManager*)OEScene->getOObjectByName("recast");
}
void PathList::update(float deltaTime) {
	for (int i = 0; i < paths.length; ++i) {
		PathInfo* info = &paths[i];
		for (int j = 0; j < info->pathCount - 1; ++j) {
			OERenderer->line2D(info->pathPoints[j], info->pathPoints[j + 1], Color::green());
			OERenderer->line2D(info->pathPoints[j + 1], info->pathPoints[j + 1] + info->pathTurnPointNormals[j + 1], Color::blue());
		}
	}
}
void PathList::finishPath(int pathidx) {
	paths[pathidx].refCount--;
	if (paths[pathidx].refCount == 0) {
		paths[pathidx].pathCount = 0;
	}
}
int PathList::newPath(Vector2 fromPos, Vector2 toPos, int refCount) {
	int ret = -1;
	PathInfo info;
	info.refCount = refCount;
	info.pathCount = recast->findPath(fromPos, toPos, info.pathPoints);
	if (info.pathCount > 1) {
		Vector2 lastNormal = info.pathPoints[1] - info.pathPoints[0];
		lastNormal.normalize();
		lastNormal.rotateClockwise90();
		info.pathTurnPointNormals[0] = Vector2::zero();// not used!
		for (int i = 1; i < info.pathCount - 1; ++i) {
			Vector2 thisDir = info.pathPoints[i + 1] - info.pathPoints[i];
			thisDir.normalize();
			thisDir.rotateClockwise90();
			Vector2 avgDir = thisDir + lastNormal;
			avgDir.normalize();
			info.pathTurnPointNormals[i] = avgDir;
			lastNormal = thisDir;
		}
		paths.push(info);
		ret = paths.length - 1;
	}
	return ret;
}