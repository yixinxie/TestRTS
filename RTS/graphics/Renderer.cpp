#include "Renderer.h"
#include <string>
#include "../misc/CharHelper.h"
#include "../misc/BasicMem.h"
using namespace OriGraphics;

Renderer::Renderer() {
}
Renderer::~Renderer() {
}
void Renderer::dispose(void){

}
void Renderer::updateCamera(Vector2 _pos, float _size) {
	cameraPos = _pos;
	cameraSize = _size;
}
void Renderer::mousePosToWorldSpace(const IntVector2& pos, Vector2* posWorldSpace) {
	// opengl implementation, should probably move to GLManager
	float aspect = (float)width / (float)height;
	float xDelta = pos.x - width / 2;
	float yDelta = height / 2 - pos.y;
	posWorldSpace->x = xDelta / (width / 2) * cameraSize * aspect + cameraPos.x;
	posWorldSpace->y = yDelta / (height / 2) * cameraSize + cameraPos.y;
}