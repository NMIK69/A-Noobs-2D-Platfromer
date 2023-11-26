#include <iostream>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "debug_utils.h"
#include "Application.h"

#include "Game.h"

int main()
{
	/*TODO:  
		- rename common.h to vec2.h
		- improve makefile
		- improve project structure
	*/

	constexpr int FPS = 60;	
	constexpr int frame_delay = 1000/FPS;

	constexpr char window_title[] = "Game!";
	constexpr int window_width = 800;
	constexpr int window_height = 512;

	int res;
	res = atexit(SDL_Quit);
	if(res != 0 ) {
		sdl_debug_print("");
		exit(EXIT_FAILURE);
	}

	Application::init(window_title, window_width, window_height);

	Game game;

	float default_dt = 1.0f/static_cast<float>(FPS);
	float dt = default_dt;

	while(game.is_running == true) {
		
		int start = static_cast<int>(SDL_GetTicks());

		game.update(dt);
		game.render();
		
		int elapsed_time = static_cast<int>(SDL_GetTicks()) - start;
		
		if(frame_delay > elapsed_time) {
			SDL_Delay(frame_delay - elapsed_time);	
			dt = default_dt; 
		}
		else dt = static_cast<float>(elapsed_time) * 1000.0f;

		//elapsed_time = static_cast<int>(SDL_GetTicks()) - start;
		//std::cout << "FPS :" << 1000.0f / static_cast<float>(elapsed_time) <<  std::endl;
	}


	Application::exit();

	exit(EXIT_SUCCESS);
}
