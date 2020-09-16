#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED

#ifdef _WIN32
#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#else
#include <SDL2/SDL.h>
#endif


#include "graphics/Vertex.cpp"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include <map>


int main(int argc, char** argv) {
	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	window = SDL_CreateWindow("C++ OpenGL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if(err != GLEW_OK){
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}

	SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_INFO);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_INFO);
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "OpenGL version: %s", glGetString(GL_VERSION));
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	// Startup end ===========================================================================

	// Game setup ===============

	Vertex vertices[] = {
		Vertex{0.5f, -0.5f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{0.5f, 0.5f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{-0.5f, -0.5f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{-0.5f, 0.5f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f}
	};
	uint32_t numVertices = 4;

	uint32_t indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	uint32_t numIndices = 6;

	IndexBuffer indexBuffer(indices, numIndices, sizeof(indices[0]));

	VertexBuffer vertexBuffer(vertices, numVertices);
	Shader shader("graphics/shaders/basic.vs", "graphics/shaders/basic.fs");
	shader.bind();

	// Game setup end ===========

	// Game environment variables
	uint64_t perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastCounter = SDL_GetPerformanceCounter();
	float delta = 0.0;

	std::map<int, int8_t> keyboard; // state of pressed keys
	SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "RAM: %d\n", SDL_GetSystemRAM());

	bool close = false;
	while(!close){ // game loop ===========
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Game frame ==============
		// Game frame end ==========

		// Frame start ====================

		vertexBuffer.bind();
		indexBuffer.bind();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

		// Frame end ======================

		SDL_GL_SwapWindow(window);

		// Event handling
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT: close = true; continue;
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
					printf("Size changed.");
				} continue;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0){
					switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						if (SDL_GetRelativeMouseMode()){
							SDL_SetRelativeMouseMode(SDL_FALSE);
						}else {
							SDL_SetRelativeMouseMode(SDL_TRUE);
						} break;
					case SDLK_F11:
						if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP){
							SDL_SetWindowFullscreen(window, 0);
						}else {
							SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						} break;
					}
				}
				keyboard[event.key.keysym.sym] = event.key.repeat;
				continue;
			case SDL_KEYUP:
				keyboard[event.key.keysym.sym] = -1;
				continue;
			case SDL_MOUSEMOTION:
				// printf("Mouse: %d\n", event.motion.xrel);
				// printf("Mouse: %d\n", event.motion.yrel);
				continue;
			}
		}

		bool print = false;
		for (auto key : keyboard){
			if (key.second != -1){
				if (!print){
					print = true;
					printf("Keyboard:");
				}
				printf(" %d|%d", key.first, key.second);
			}
		}
		if (print){
			print = false;
			printf("\n");
		}


		// FPS counter start ==============
		uint64_t endCounter = SDL_GetPerformanceCounter();
		uint64_t timeElapsed = endCounter - lastCounter;
		delta = ((float)timeElapsed)/(float)perfCounterFrequency;
		uint32_t FPS = (uint32_t)(((float)perfCounterFrequency)/(float)timeElapsed);
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "FPS: %d\n", FPS);
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Delta: %g\n", delta);
		lastCounter = endCounter;
		// FPS counter end ================
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
