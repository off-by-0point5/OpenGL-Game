/*
 * indexBuffer.cpp
 *
 *  Created on: 08.08.2020
 *      Author: offbyone
 */

#include "IndexBuffer.h"

#include <cstdint>
#include <GL/glew.h>
#include "Vertex.cpp"

IndexBuffer::IndexBuffer(void* data, uint32_t numIndices, uint8_t elementSize) {
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
