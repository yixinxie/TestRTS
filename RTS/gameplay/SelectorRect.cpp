#include "SelectorRect.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
SelectorRect::SelectorRect() {
	leftButtonDown = false;
}
SelectorRect::~SelectorRect() {

}
void SelectorRect::init() {
	int textureId = G::instance()->renderer->newSpriteSheet(1000, 200, "assets/greenbar.png");
	G::instance()->renderer->newSprite(textureId, Vector2(0,0), Vector2(0,0));
}
void SelectorRect::update(float deltaTime) {

}