#include "AABBManager.h"
#include "misc/G.h"
#include "../plugins/aabbcc/AABB.h"
using namespace aabb;
AABBManager::AABBManager() {
	setName("aabb");
}

AABBManager::~AABBManager() {
}

void AABBManager::init() {
	// Fattening factor.
	const double fatten = 0.1;

	// Periodicity of the simulation box.
	std::vector<bool> periodicity({ true, true });

	// Size of the simulation box.
	std::vector<double> boxSize({ 100, 100 });

	unsigned int nSmall = 100;


	// Create the AABB trees.
	Tree treeSmall(fatten, periodicity, boxSize, nSmall);
	///


	const double radius = 1.0;

	// Particle index (key).
	unsigned int index = 1;

	// Set the particle position.
	std::vector<double> position({ 10.0, 10.0 });

	// Compute lower and upper AABB bounds.
	std::vector<double> lowerBound({ position[0] - radius, position[1] - radius });
	std::vector<double> upperBound({ position[0] + radius, position[1] + radius });

	// Insert particle into the tree.
	//treeSmall.insertParticle(index, position, lowerBound, upperBound);
	treeSmall.insertParticle(index, position, radius);

	std::vector<double> test_lowerBound({ 5, 5 });
	std::vector<double> test_upperBound({ 15, 15 });
	int32 sz = sizeof(test_lowerBound);
	sz = sizeof(Vector2);
	// Create the AABB.
	AABB aabb(test_lowerBound, test_upperBound);

	// Query the tree for overlap with the AABB.
	std::vector<unsigned int> particles = treeSmall.query(aabb);
	int sdf = 0;
}
