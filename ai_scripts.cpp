#include "ai_scripts.h"
#include "ECS/Components/Components.h"

void vertical_enemy_movment(Entity *ent)
{
	Transform *et = ent->get_component<Transform>(ComponentType::TRANSFORM);	
	AI *ea = ent->get_component<AI>(ComponentType::AI);	

	if(et->pos.x < ea->start.x || et->pos.x > ea->end.x)
		et->vel.x *= -1.0f;
		
}
