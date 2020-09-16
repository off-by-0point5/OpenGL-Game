/*
 * Element.cpp
 *
 *  Created on: 17.08.2020
 *      Author: offbyone
 */

#include "Element.h"

Element::Element(float x, float y, float width, float height, uint16_t texture) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->texture = texture;
}

Element::~Element() {
	// TODO Auto-generated destructor stub
}

void Element::draw() {
	printf("drawn element");
}
