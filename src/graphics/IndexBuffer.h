/*
 * indexBuffer.h
 *
 *  Created on: 08.08.2020
 *      Author: offbyone
 */

#pragma once
#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_
#include <cstdint>
#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer(void* data, uint32_t numIndices, uint8_t elementSize);
	virtual ~IndexBuffer();
	void bind();
	void unbind();
private:
	GLuint bufferId;
};

#endif /* INDEXBUFFER_H_ */
