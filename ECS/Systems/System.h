#ifndef GAME_BASE_SYSTEM_H
#define GAME_BASE_SYSTEM_H

#include <list>
#include <bitset>
#include "../Components/Components.h"

using Entity_ID = std::size_t;

class System
{
public:
	System() = default;
	virtual ~System() = default;
	virtual void add_entity(Entity_ID id);

protected:
	std::list<Entity_ID> entities;
	/* only Entities with at least the same or more components can be added to this
	 * system */
	Signature system_signature{0};
};

#endif
