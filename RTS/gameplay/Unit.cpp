#include "Unit.h"
#include "../misc/G.h"
#include "../misc/CharHelper.h"
#include "../misc/Macros.h"
Unit::Unit(){

}
Unit::~Unit() {

}
void Unit::init(Vector2 pos, const char* id) {
	textureId = OERenderer->newSpriteSheet("assets/arrows.png");
	spriteDescId = OERenderer->newSprite(textureId, pos, id);
	this->pos = pos;
}
void Unit::update(float deltaTime) {
	const float speed = 2.5f;
	if (animState == UnitAnimStates::Moving)
	{
		Vector2 dir = targetPos - pos;
		if (dir.simpleMag() == 0){
			
			animState = UnitAnimStates::Idle;
		}
		else {
			dir.normalize();
		}

		pos += dir * deltaTime * speed;
		float rot = atan2(dir.y, dir.x) - Math_PI / 2.0f;
		OERenderer->updateSprite(textureId, spriteDescId, pos, rot);
	}
}

const Vector2& Unit::getPos(void) const {
	return pos;
}

void Unit::setMoveTarget(const Vector2& _targetPos) {
	targetPos = _targetPos;
	animState = UnitAnimStates::Moving;
	//printf_s("%f, %f\n", _targetPos.x, _targetPos.y);

	OERenderer->line2D(pos, _targetPos, Color::blue());
}