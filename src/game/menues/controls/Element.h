/*
 * Element.h
 *
 *  Created on: 17.08.2020
 *      Author: offbyone
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_
#include <iostream>

class Element {
public:
	Element(float x, float y, float width, float height, uint16_t texture);
	virtual ~Element();
	void draw();
protected:
	uint16_t texture;
	float x, y, width, height;
};

#endif /* ELEMENT_H_ */
