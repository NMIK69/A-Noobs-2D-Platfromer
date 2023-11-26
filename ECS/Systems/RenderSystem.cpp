#include "RenderSystem.h"
#include "../../Application.h"
#include "../EntityManager.h"
#include "../Components/Components.h"


extern EntityManager g_entity_manager;

RenderSystem::RenderSystem()
{
	system_signature[static_cast<int>(ComponentType::TRANSFORM)] = true;
	system_signature[static_cast<int>(ComponentType::SPRITE)] = true;
}

void RenderSystem::update()
{
	std::list<Entity_ID>::iterator itr = entities.begin();
	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "RenderSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);
		Sprite *spr = ent->get_component<Sprite>(ComponentType::SPRITE);

		spr->screen_pos.x = trans->pos.x - camera->x;
		spr->screen_pos.y = trans->pos.y - camera->y;
		itr++;
	}
}

void RenderSystem::render()
{
	std::list<Entity_ID>::iterator itr = entities.begin();
	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "RenderSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		Sprite *spr = ent->get_component<Sprite>(ComponentType::SPRITE);

		SDL_RenderCopy(Application::renderer, spr->atlas, &spr->atlas_pos, &spr->screen_pos);	
		itr++;
	}
	
}

void RenderSystem::set_camera(SDL_Rect *cam)
{
	camera = cam;
}
