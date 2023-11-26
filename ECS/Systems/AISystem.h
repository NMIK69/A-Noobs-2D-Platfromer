#ifndef GAME_AI_SYSTEM_H
#define GAME_AI_SYSTEM_H

#include <list>
#include <bitset>
#include "../Components/Components.h"
#include "System.h"


class AISystem : public System
{
public:
	AISystem();
	void update();
};

#endif
