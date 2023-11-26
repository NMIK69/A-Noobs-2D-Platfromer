#include "AISystem.h"
#include "../EntityManager.h"


extern EntityManager g_entity_manager;

AISystem::AISystem()
{
	system_signature[static_cast<int>(ComponentType::AI)] = true;
	system_signature[static_cast<int>(ComponentType::TRANSFORM)] = true;
}

void AISystem::update()
{
	std::list<Entity_ID>::iterator itr = entities.begin();

	while(itr != entities.end()) {

		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "AISystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		AI *ai = ent->get_component<AI>(ComponentType::AI);	
		ai->script(ent);
		itr++;
	}
}
