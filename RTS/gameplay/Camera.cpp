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
	size = 10.0f;
	G::instance()->renderer->updateCamera(pos, size);
}
void Camera::update(float deltaTime) {
	//pos.x += 0.01f;
	G::instance()->renderer->updateCamera(pos, size);
}
void Camera::setSize(float _scale) {
	size = _scale;
	G::instance()->renderer->updateCamera(pos, size);
}
float Camera::getSize() const {
	return size;
}
void Camera::setPos(Vector2 _pos) {
	pos = _pos;
	G::instance()->renderer->updateCamera(pos, size);
}