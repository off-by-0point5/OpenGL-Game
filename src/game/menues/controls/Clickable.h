/*
 * Clickable.h
 *
 *  Created on: 17.08.2020
 *      Author: offbyone
 */

#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include "Element.h"

class Clickable : protected Element {
public:
	Clickable(float x, float y, float width, float height, uint16_t texture, bool disabled):Element(x, y, width, height, texture){
		this->disabled = disabled;
	};
	Clickable(float x, float y, float width, float height, uint16_t texture):Element(x, y, width, height, texture){
		this->disabled = false;
	};
	virtual ~Clickable();
	void onClick();
	void onRelease();
	void onHover();
	void setDisabled(bool disable);
	using Element::draw;
protected:
	bool disabled;
};

#endif /* CLICKABLE_H_ */
