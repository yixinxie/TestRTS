#include "Terrain.h"
#include "../misc/G.h"
Terrain::Terrain() {
	setName("terrain");
}
Terrain::~Terrain() {

}
void Terrain::init() {
	//textureId = G::instance()->renderer->newSpriteSheet(1000, 200, "assets/dirt.jpg");
	textureId = G::instance()->renderer->newSpriteSheet("assets/terrain_packed.png");
	spriteId = G::instance()->renderer->newSprite(textureId, pos, Vector2(0,0));
}
void Terrain::update(float deltaTime) {
	
}
void Terrain::updateRectScale(Vector2 _scale) {
	scale = _scale;
	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
}
void Terrain::updateRectPos(Vector2 _pos) {
	pos = _pos;
	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
}