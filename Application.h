#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <string>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GAME_SCREEN_DEFAULT_WIDTH 800
#define GAME_SCREEN_DEFAULT_HEIGHT 640

namespace Application
{
	void init(const std::string &title="Title", 
		int width=GAME_SCREEN_DEFAULT_WIDTH, 
		int height=GAME_SCREEN_DEFAULT_HEIGHT, 
		uint32_t wflags=0,
		uint32_t rflags=SDL_RENDERER_ACCELERATED);

	
	void exit();


	/* TODO: make static with getter functions */
	extern SDL_Window *window;
	extern int window_width; 
	extern int window_height;
	extern SDL_Renderer *renderer;

};

#endif
