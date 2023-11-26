#include "AnimationSystem.h"
#include "../EntityManager.h"
#include "../Components/Components.h"


extern EntityManager g_entity_manager;

AnimationSystem::AnimationSystem()
{
	system_signature[static_cast<int>(ComponentType::ANIMATION)] = true;
}

void AnimationSystem::update(float dt)
{
	std::list<Entity_ID>::iterator itr = entities.begin();

	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "AnimationSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);
			continue;
		}

		Animation *ani = ent->get_component<Animation>(ComponentType::ANIMATION);
		ani->time_s += dt;
		ani->script(ent);

		itr++;
	}
}
