#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include <SDL2/SDL.h>
#include <iostream>

struct Vec2
{
	float x{};
	float y{};
};

std::ostream &operator<<(std::ostream &out, const Vec2 &vec);

std::ostream &operator<<(std::ostream &out, const SDL_Rect &rec);

bool has_overlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh);

#endif
