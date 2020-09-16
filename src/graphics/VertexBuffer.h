/*
 * vertexbuffer.h
 *
 *  Created on: 08.08.2020
 *      Author: offbyone
 */

#pragma once
#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_
#include <cstdint>
#include <GL/glew.h>

class VertexBuffer {
public:
	VertexBuffer(void* data, uint32_t numVertices);
	virtual ~VertexBuffer();
	void bind();
	void unbind();
private:
	GLuint bufferId;
	GLuint vao;
};

#endif /* VERTEXBUFFER_H_ */
