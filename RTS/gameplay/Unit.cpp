#include "Unit.h"
#include "../misc/G.h"
Unit::Unit() {

}
Unit::~Unit() {

}
void Unit::init() {
	G::instance()->renderer->newSprite(pos, Vector2(0,0));
}