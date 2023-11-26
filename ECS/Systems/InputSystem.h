#ifndef GAME_INPUT_SYSTEM_H
#define GAME_INPUT_SYSTEM_H

#include <list>
#include <SDL2/SDL.h>
#include "System.h"

class Game;

class InputSystem : public System
{
public:
	InputSystem();
	void update(float dt);
	void handle_key_down(float dt);
	void handle_key_up(float dt);

	Game *game;
private:
	SDL_Event event;
};


#endif
