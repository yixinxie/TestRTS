#include "AABBManager.h"
#include "misc/G.h"
#include "../plugins/aabbcc/AABB.h"
using namespace aabb;
AABBManager::AABBManager() {
	setName("aabb");
	currentAgentIndex = 1;
}

AABBManager::~AABBManager() {
}

void AABBManager::init() {
	// Fattening factor.

	// Periodicity of the simulation box.
	const bool periodicity[2] = { true, true };

	// Size of the simulation box.
	aabbReal boxSize[2] = { 64.0f, 64.0f };

	//unsigned int nSmall = 100;

	// Create the AABB trees.
	//Tree treeSmall(fatten, periodicity, boxSize, nSmall);
	///
	aabbTree.setBoxSize(boxSize);
	aabbTree.setPeriodicity(periodicity);

	const double radius = 1.0;

	// Particle index (key).
	unsigned int index = 1;

	// Set the particle position.
	aabbReal position[2] = { 10.0, 10.0 };

	// Compute lower and upper AABB bounds.
	/*aabbReal lowerBound[2] = { position[0] - radius, position[1] - radius };
	aabbReal upperBound[2] = { position[0] + radius, position[1] + radius };*/

	// Insert particle into the tree.
	//treeSmall.insertParticle(index, position, lowerBound, upperBound);
	aabbTree.insertParticle(index, position, radius);

	aabbReal test_lowerBound[2] = { 5, 5 };
	aabbReal test_upperBound[2] = { 15, 15 };
	int32 sz = sizeof(test_lowerBound);
	sz = sizeof(Vector2);
	// Create the AABB.
	AABB aabb(test_lowerBound, test_upperBound);

	sz = sizeof(aabb);
	sz = sizeof(aabbTree);
	// Query the tree for overlap with the AABB.
	std::vector<unsigned int> particles = aabbTree.query(aabb);
	int sdf = 0;
}

int32 AABBManager::addAgent(Vector2 _pos, float _radius) {
	aabbReal position[2] = { _pos.x, _pos.y };
	aabbReal radius = _radius;
	aabbTree.insertParticle(currentAgentIndex, position, radius);
	int32 ret = currentAgentIndex;
	currentAgentIndex++;
	return ret;
}

void AABBManager::updateAgent(int32 idx, Vector2 _pos, float _radius) {
	aabbReal position[2] = { _pos.x, _pos.y };
	aabbReal radius = _radius;
	aabbTree.updateParticle(idx, position, radius);
}

void AABBManager::query(Vector2 _pos, float _radius) {


	aabbReal test_lowerBound[2] = { _pos.x - _radius, _pos.y - _radius };
	aabbReal test_upperBound[2] = { _pos.x + _radius, _pos.y + _radius };

	AABB aabbQuery(test_lowerBound, test_upperBound);

	std::vector<unsigned int> result = aabbTree.query(aabbQuery);
	for (int i = 0; i < result.size(); ++i) {
		int sdf = 0;

	}
}