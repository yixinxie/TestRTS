#pragma once
#include "../misc/ArrayT.h"
#include "../misc/SimpleVector.h"
/* 2d implementation of a simple AABB tree*/
struct AABBNode{
	const float fatMargin = 0.1f;
	int32 child_0, child_1;
	Vector2 fatBBMin, fatBBMax;

};