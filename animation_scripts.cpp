#include "animation_scripts.h"
#include "ECS/Components/Components.h"

void coin_animation(Entity *ent)
{
	Animation *ani = ent->get_component<Animation>(ComponentType::ANIMATION);
	Sprite *spr = ent->get_component<Sprite>(ComponentType::SPRITE);

	if(ani->time_s < 0.15f) return;
		
	ani->time_s = 0.0f;	

	spr->atlas_pos.x += spr->atlas_pos.w;
	if(spr->atlas_pos.x > 160) spr->atlas_pos.x = 0;
}

void enemy_animation(Entity *ent)
{
	Animation *ani = ent->get_component<Animation>(ComponentType::ANIMATION);
	Sprite *spr = ent->get_component<Sprite>(ComponentType::SPRITE);
	Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);	

	if(ani->time_s < 0.15f) return;
		
	ani->time_s = 0.0f;	

	spr->atlas_pos.x += spr->atlas_pos.w;
	if(spr->atlas_pos.x > 64) spr->atlas_pos.x = 0;

	 if(trans->vel.x == 0) {
		spr->atlas_pos.x = 0;
	}
}

void player_animation(Entity *ent)
{
	Animation *ani = ent->get_component<Animation>(ComponentType::ANIMATION);
	Sprite *spr = ent->get_component<Sprite>(ComponentType::SPRITE);
	Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);	

	if(ani->time_s < 0.15f) return;
		
	ani->time_s = 0.0f;	

	spr->atlas_pos.x += spr->atlas_pos.w;
	if(spr->atlas_pos.x > 96) spr->atlas_pos.x = 0;

	if(trans->vel.x > 0) {
		spr->atlas_pos.y = 0;
	}
	else if(trans->vel.x < 0){
		spr->atlas_pos.y = 32;
	}

	else if(trans->vel.x == 0) {
		spr->atlas_pos.x = 0;
	}

}
