#ifndef GAME_ANIMATION_SYSTEM_H
#define GAME_ANIMATION_SYSTEM_H

#include <list>
#include "System.h"

class AnimationSystem : public System
{
public:
	AnimationSystem();
	void update(float dt);
};

#endif
