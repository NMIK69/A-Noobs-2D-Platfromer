#ifndef GAME_ENTITY_MANAGER_H
#define GAME_ENTITY_MANAGER_H


#include "Entity.h"
#include "../constants.h"
#include <array>
#include <deque>


using Entity_ID = std::size_t;


/* TODO: count alive entities and error when we dont have 
         any more ids to create new entities */
class EntityManager
{
public:
	EntityManager();

	~EntityManager();
		
	Entity_ID create_entity();
	
	Entity *get_entity(Entity_ID id);
	
	void delete_entity(Entity_ID id);
	
private:
	std::array<Entity*, MAX_ENTITIES> ents;
	std::deque<Entity_ID> available_ids;
};

#endif
