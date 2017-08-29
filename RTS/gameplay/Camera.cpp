#include "Camera.h"
#include "../misc/G.h"
#include "../misc/WindowsInput.h"
Camera::Camera() {
	setName("camera");
}
Camera::~Camera() {

}
void Camera::init() {
	pos = Vector2(0.0f, 0.0f);
}
void Camera::update(float deltaTime) {
	
}
void Camera::setSize(float _scale) {
	size = _scale;
	G::instance()->renderer->updateCamera(pos, size);
}
void Camera::setPos(Vector2 _pos) {
	pos = _pos;
	G::instance()->renderer->updateCamera(pos, size);
}