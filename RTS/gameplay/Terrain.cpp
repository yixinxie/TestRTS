#include "Terrain.h"
#include "../misc/G.h"
#include "../misc/CharHelper.h"
Terrain::Terrain() {
	setName("terrain");
}
Terrain::~Terrain() {
	deallocND(grid);
}
void Terrain::init() {
	CharBuffer* cb = CharHelper::loadBinaryFile("assets/terrain_grid.bin");
	grid = allocArray<byte>(dim * dim, "terrain_grid_array");
	memcpy_s(grid, dim * dim, cb->buffer, dim * dim);
	cb->dispose();
	textureId = G::instance()->renderer->newSpriteSheet("assets/terrain_packed.png");
	const char* walkableId = "dirt";
	const char* obstacleId = "water";
	for (int32 y = 0; y < dim; ++y) {
		for (int32 x = 0; x < dim; ++x) {
			int32 idx = x + y * dim;
			spriteId = G::instance()->renderer->newSprite(textureId, pos, (grid[idx] == 0) ? walkableId : obstacleId);
			Vector2 tilePos = Vector2(x, y);

			G::instance()->renderer->updateSprite(textureId, spriteId, tilePos, 0.0f, Vector2(1, 1));
		}
	}
	/*spriteId = G::instance()->renderer->newSprite(textureId, pos, "dirt");
	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, Vector2(1, 1));

	spriteId = G::instance()->renderer->newSprite(textureId, pos + Vector2(4, 0), "water");
	G::instance()->renderer->updateSprite(textureId, spriteId, pos + Vector2(4, 0), 0.0f, Vector2(1, 1));*/
}
void Terrain::update(float deltaTime) {
	
}
//void Terrain::updateRectScale(Vector2 _scale) {
//	scale = _scale;
//	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
//}
//void Terrain::updateRectPos(Vector2 _pos) {
//	pos = _pos;
//	G::instance()->renderer->updateSprite(textureId, spriteId, pos, 0.0f, scale);
//}