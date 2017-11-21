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

	Vector2 res = pointToLine(Vector2(0, 0), Vector2(1, 1), Vector2(1, 0));
	int sdf = 0;
}
Vector2 Unit::pointToLine(Vector2 line_pos, Vector2 line_vec, Vector2 point_pos) const{
	Vector2 ret;
	Vector2 dir = line_vec;
	Vector2 perp;
	perp.x = -dir.y;
	perp.y = dir.x;
	float t = 0.0f;
	if (dir.x == 0.0f) {
		// the line is vertical
		ret.x = line_pos.x;
		ret.y = point_pos.y;
	}
	else if (dir.y == 0.0f) {
		// the line is horizontal
		ret.x = point_pos.x;
		ret.y = line_pos.y;
	}
	else {
		t = (dir.x * point_pos.y - dir.x * line_pos.y - point_pos.x * dir.y + line_pos.x * dir.y) / (perp.x * dir.y - dir.x * perp.y);
		ret.x = point_pos.x + t * perp.x;
		ret.y = point_pos.y + t * perp.y;
	}
	return ret;
}


void Unit::update(float deltaTime) {
	
	if (dbgid == 1) {
		int sdf = 0;
	}
	if (animState == UnitAnimStates::Moving)
	{
		Vector2 dir = targetPos - pos;
		if (pathPointIndex == -1) {
			if (dir.magSquared() < 0.44f) {
				animState = UnitAnimStates::Idle;
			}
		}
		else{
			Vector2 projected = pointToLine(targetPos, pathTurnPointNormals[pathPointIndex], pos);
			float distToTurnLine = projected.distanceTo(pos);
			if (distToTurnLine < 0.2f) { // could use dist squared here.
				pathPointIndex++;
				assert(pathPointIndex <= pathCount);
				if (pathPointIndex == pathCount) {
					animState = UnitAnimStates::Idle;
				}
				else {
					targetPos = pathPoints[pathPointIndex];
				}
			}
			
		}
		dir.normalize();
		dir = boidsMovement(dir);// adjusted dir
		dir = staticCollisionPass(dir);
		pos += dir * deltaTime * speed;
		phys->updateAgent(b2body, pos);

		lastPos = pos;
		// calculate rotation
		float rot = atan2(dir.y, dir.x) - Math_PI / 2.0f;
		OERenderer->updateSprite(textureId, spriteDescId, pos, rot);

		for (int i = 0; i < pathCount - 1; ++i) {
			OERenderer->line2D(pathPoints[i], pathPoints[i + 1], Color::green());
			OERenderer->line2D(pathPoints[i], pathPoints[i] + pathTurnPointNormals[i], Color::blue());
		}
		
	}
	OERenderer->circle(pos, collisionRadius, Color::white());
}
// a partial implementation of a 2d movement raytest.
Vector2 Unit::staticCollisionPass(Vector2 desiredVelocity) const {
	b2RayCastCallback cb;
	if (phys->raycast(pos, pos +  desiredVelocity * collisionRadius, &cb) == false){
		return desiredVelocity;
	}
	Vector2 normal = Vector2(cb.normal.x, cb.normal.y);
	normal.rotateClockwise90();
	float dotprod = normal.dot(desiredVelocity);
	if (dotprod < 0) {
		normal.x = -normal.x;
		normal.y = -normal.y;
	}
	normal.x *= cb.fraction;
	normal.y *= cb.fraction;
	return normal;

}
Vector2 Unit::boidsMovement(Vector2 desiredVelocity) {
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
		if (boids == this || boids == nullptr) continue;
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
	int32 thisPathCount = recast->findPath(pos, _targetPos, pathPoints);
	if (thisPathCount > 1) {
		pathCount = thisPathCount;
		animState = UnitAnimStates::Moving;
		pathPointIndex = 1;
		targetPos = pathPoints[pathPointIndex];
		Vector2 lastNormal = pathPoints[1] - pathPoints[0];
		lastNormal.normalize();
		lastNormal.rotateClockwise90();
		pathTurnPointNormals[0] = Vector2::zero();// not used!
		for (int i = 1; i < pathCount - 1; ++i) {
			Vector2 thisDir = pathPoints[i + 1] - pathPoints[i];
			thisDir.normalize();
			thisDir.rotateClockwise90();
			Vector2 avgDir = thisDir + lastNormal;
			avgDir.normalize();
			pathTurnPointNormals[i] = avgDir;
			lastNormal = thisDir;
		}
	}
	else {
		int sdf = 0;
	}
	
}