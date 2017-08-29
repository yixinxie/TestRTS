#include "Unit.h"
#include "../misc/G.h"
Unit::Unit(){

}
Unit::~Unit() {

}
void Unit::init(Vector2 pos, Vector2 uv) {
	textureId = OERenderer->newSpriteSheet(512, 512, "assets/arrows.png");
	spriteDescId = OERenderer->newSprite(textureId, pos, uv);
	this->pos = pos;
}
void Unit::update(float deltaTime) {
	pos.x += deltaTime * 1.0f;
	OERenderer->updateSprite(textureId, spriteDescId, pos);
}