#include "OObject.h"
#include "../misc/G.h"
OObject::OObject() {
	name[0] = 0;
}
OObject::~OObject() {
}
void OObject::setName(const char* str) {
	strcpy_s(name, str);
}
const char* OObject::getName(void) {
	return name;
}
//void OObject::update() {
//	G::instance()->renderer->newSprite(pos, Vector2(0,0));
//}