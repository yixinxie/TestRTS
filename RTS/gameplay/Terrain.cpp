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
	//printf_s("\n");
	for (int32 y = 0; y < dim; ++y) {
		for (int32 x = 0; x < dim; ++x) {
			int32 idx = x + y * dim;
			spriteId = G::instance()->renderer->newSprite(textureId, pos, (grid[idx] == 0) ? walkableId : obstacleId);
			Vector2 tilePos = Vector2(x, y);
			//printf_s("%d", grid[idx]);
			G::instance()->renderer->updateSprite(textureId, spriteId, tilePos, 0.0f, Vector2(1, 1));
		}
		//printf_s("\n");
	}
}
