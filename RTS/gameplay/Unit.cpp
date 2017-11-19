#include "Unit.h"
#include "AABBManager.h"
#include "StaticCollision.h"
#include "RecastManager.h"
#include "../misc/G.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
Unit::Unit(){
	pathPointIndex = 0;
	speed = 2.5f;
	animState = UnitAnimStates::Idle;
	dbgid = -1;
}
Unit::~Unit() {

}
void Unit::init(Vector2 _pos, const char* id) {
	collisionRadius = 1.0f;
	pos = _pos;
	lastPos = _pos;
	textureId = OERenderer->newSpriteSheet("assets/arrows.png");
	spriteDescId = OERenderer->newSprite(textureId, pos, id);
	

	recast = (RecastManager*)OEScene->getOObjectByName("recast");

	//aabb = (AABBManager*)OEScene->getOObjectByName("aabb");
	//aabbId = aabb->addAgent(pos, collisionRadius);

	phys = (StaticCollision*)OEScene->getOObjectByName("static_collision");
	b2body = phys->addAgent(pos, (void*)this);
}
void Unit::update(float deltaTime) {
	
	if (dbgid == 1) {
		int sdf = 0;
	}
	if (animState == UnitAnimStates::Moving)
	{
		Vector2 dir = targetPos - pos;
		if (dir.magSquared() < 0.44f) {
			if (pathPointIndex == -1){
				animState = UnitAnimStates::Idle;
			}
			else {
				pathPointIndex++;
				if (pathPointIndex == pathCount) {
					animState = UnitAnimStates::Idle;
				}
				else {
					targetPos = pathPoints[pathPointIndex];
				}
			}
		}
		else {
			dir.normalize();
		}
		dir = updateMovement(dir);// adjusted dir
		pos += dir * deltaTime * speed;
		phys->updateAgent(b2body, pos);

		lastPos = pos;
		// calculate rotation
		float rot = atan2(dir.y, dir.x) - Math_PI / 2.0f;
		OERenderer->updateSprite(textureId, spriteDescId, pos, rot);

		for (int i = 0; i < pathCount - 1; ++i) {
			OERenderer->line2D(pathPoints[i], pathPoints[i + 1], Color::green());
		}
		
	}
	OERenderer->circle(pos, collisionRadius, Color::white());
}
Vector2 Unit::updateMovement(Vector2 desiredVelocity) {
	const float repulsionCoeff = 2.0f;
	const float repulsionDist = 0.5f;
	Vector2 adjustedVelocity;
	Vector2 pos2d = pos;
	b2QueryCallback overlapResults;
	int count = phys->overlap(pos2d, collisionRadius * 2.0f, &overlapResults);
	Vector2 basePos = pos;
	Vector2 aggregatedInfluence = Vector2::zero();
	float originalVelocityCoeff = 1.0f;
	for (int i = 0; i < count; ++i) {
		Unit* boids = (Unit*)overlapResults.userData[i];
		if (boids == this) continue;
		if (boids->dbgid == 1)
		{
			int sdf = 0;
		}
		Vector2 neighbourBasePos = boids->pos;
		float distanceToSelf = neighbourBasePos.distanceTo(basePos);
		distanceToSelf -= (boids->collisionRadius + collisionRadius);
		if (//distanceToSelf >= 0.0f && 
			distanceToSelf < repulsionDist) {
			Vector2 repulVec = basePos - neighbourBasePos;
			repulVec.normalize();
			aggregatedInfluence += repulVec * (repulsionDist - distanceToSelf) * repulsionCoeff;
			if (boids->animState == (byte)UnitAnimStates::Idle) {
				// possibly the only reason this function cannot be const...
				boids->makeSpace(repulVec);
			}
			if (distanceToSelf < 0.0f) {
				originalVelocityCoeff = 0.0f;
			}
		}
	}

	adjustedVelocity = desiredVelocity * originalVelocityCoeff + aggregatedInfluence;
	adjustedVelocity.normalize();

	return adjustedVelocity;
}
void Unit::makeSpace(Vector2 _dir) {
	animState = UnitAnimStates::Moving;
	targetPos = pos - _dir * collisionRadius;
	pathPointIndex = -1;
	if (dbgid == 1) {
		int sdf = 0;
	}
}

const Vector2& Unit::getPos(void) const {
	return pos;
}

void Unit::setMoveTarget(const Vector2& _targetPos) {
	
	//printf_s("%f, %f\n", _targetPos.x, _targetPos.y);
	
	OERenderer->line2D(pos, _targetPos, Color::blue());
	
	pathCount = recast->findPath(pos, _targetPos, pathPoints);
	if (pathCount > 1) {
		animState = UnitAnimStates::Moving;
		pathPointIndex = 1;
		targetPos = pathPoints[pathPointIndex];
	}
	
}