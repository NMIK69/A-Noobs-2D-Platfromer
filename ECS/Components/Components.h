#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "../../common.h"
#include <bitset>
class Entity;

enum class ComponentType
{
	INVALID_TYPE = -1,
	TRANSFORM = 0,
	SPRITE,
	AI,
	ANIMATION,
	MAX_COMPONENT_TYPES
};

using Signature = std::bitset<static_cast<int>(ComponentType::MAX_COMPONENT_TYPES)>;
//bool operator==(const Signature &sig1, const Signature &sig2);
bool operator>=(const Signature &lhs, const Signature &rhs);


/* Base */
struct Component
{
	Component() 
	: type{ComponentType::INVALID_TYPE} 
	{};

	Component(ComponentType t) 
	: type{t} 
	{}

	virtual ~Component() = default; 


	ComponentType type;	
};


struct Animation : Component
{
	Animation()
	: Component{ComponentType::ANIMATION},
	  script{nullptr}
	{}

	Animation(void (*fp)(Entity *ent))
	: Component{ComponentType::ANIMATION},
	  script{fp},
	  time_s{0}
	{}

	void (*script)(Entity *ent);
	float time_s;
};


struct AI : Component
{
	AI()
	: Component{ComponentType::AI},
	 start{0,0}, end{0,0}, script{nullptr}
	{}

	AI(void (*fp)(Entity*), Vec2 sta, Vec2 en)
	: Component{ComponentType::AI},
	 start{sta}, end{en}, script{fp}
	{}

	Vec2 start;
	Vec2 end;
	void (*script)(Entity *ent);
};


struct Transform : Component
{
	Transform()
	: Component{ComponentType::TRANSFORM}
	{};
	Transform(float px, float py, float fr=1, float ay=0, float vx=0, float vy=0) 
	: Component{ComponentType::TRANSFORM}, 
	  pos{px, py}, 
	  vel{vx, vy},
	  grav{0,ay},
	  friction{fr}
	{}

	Vec2 pos;
	Vec2 vel;
	Vec2 grav;

	float friction;
};


struct Sprite : Component
{
	Sprite() {};
	Sprite(int sx, int sy, int sw, int sh, int dx, int dy, SDL_Texture *ap=nullptr) 
	: Component{ComponentType::SPRITE}, 
	  atlas_pos{.x=sx, .y=sy, .w=sw, .h=sh},
	  screen_pos{.x=dx, .y=dy, .w=sw, .h=sh},
	  atlas{ap}
	{}
	
	SDL_Rect atlas_pos;
	SDL_Rect screen_pos;
	SDL_Texture *atlas;
};

#endif
