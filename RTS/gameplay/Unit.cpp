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
	//pos.x += deltaTime * 1.0f;
	OERenderer->updateSprite(textureId, spriteDescId, pos);
	OERenderer->line2D(pos, pos + Vector2::one(), Color::blue());
}