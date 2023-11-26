#include "System.h"
#include "../EntityManager.h"

extern EntityManager g_entity_manager;

void System::add_entity(Entity_ID id)
{
	Entity *ent = g_entity_manager.get_entity(id);	
	if(ent == nullptr) 
		return;

	/* check if the entity has at least the components that are nesessary to
	 * be added to the system */
	Signature ent_sig = ent->get_signature();
	if(ent_sig >= system_signature) {
		entities.push_back(id);
	}

}
