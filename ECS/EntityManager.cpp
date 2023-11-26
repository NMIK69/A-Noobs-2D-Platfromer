#include "EntityManager.h"

EntityManager::EntityManager()
: ents{}
{
	for(Entity_ID i = 0; i < MAX_ENTITIES; i++) {
		available_ids.push_back(i);
	}
}

EntityManager::~EntityManager()
{
	for(Entity_ID i = 0; i < MAX_ENTITIES; i++) {
		delete ents[i];
	}
}

Entity_ID EntityManager::create_entity() 
{
	assert(available_ids.empty() == false);

	Entity *new_ent = new Entity{};

	Entity_ID new_ent_id = available_ids.front();
	available_ids.pop_front();

	ents[new_ent_id] = new_ent;

	return new_ent_id;
}

Entity *EntityManager::get_entity(Entity_ID id)
{
	return ents[id];
}

void EntityManager::delete_entity(Entity_ID id)
{
	if(ents[id] != nullptr) {
		available_ids.push_back(id);
		delete ents[id];
		ents[id] = nullptr;
	}
}
