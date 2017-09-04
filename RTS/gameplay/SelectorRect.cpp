#include "SelectorRect.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
SelectorRect::SelectorRect() {
	leftButtonDown = false;
	setName("selector_rect");
}
SelectorRect::~SelectorRect() {

}
void SelectorRect::init() {
	textureId = G::instance()->renderer->newSpriteSheet("assets/greenbar.png");
	pos = Vector2(0.0f, 0.0f);
	spriteId = G::instance()->renderer->newSprite(textureId, pos, Vector2(0,0));
}
void SelectorRect::update(float deltaTime) {
	
}
void SelectorRect::updateRectScale(Vector2 _scale) {
	scale = _scale;
	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
}
void SelectorRect::updateRectPos(Vector2 _pos) {
	pos = _pos;
	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
}