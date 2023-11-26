#ifndef GAME_RENDER_SYSTEM_H
#define GAME_RENDER_SYSTEM_H

#include <list>
#include <SDL2/SDL.h>
#include "System.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	void update();

	void render();

	void set_camera(SDL_Rect *cam);
	
private:
	SDL_Rect *camera;
};

#endif
