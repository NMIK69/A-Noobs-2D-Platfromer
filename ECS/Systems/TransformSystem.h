#ifndef GAME_TRANSFORM_SYSTEM_H
#define GAME_TRANSFORM_SYSTEM_H

#include <list>
#include <vector>
#include "../Components/Components.h"
#include "System.h"


class Entity;

/* TODO: Maybe rename it to MovementSystem ?*/
class TransformSystem : public System
{

public:
	TransformSystem();
	void update(float dt);
	
	void set_world_map(const std::vector<std::vector<int>> &map);
private:
	std::vector<std::vector<int>> world_map;

	int map_height;
	int map_width;
	int map_pixel_height;
	int map_pixel_width;


	void check_world_colission_horizontal(Entity *ent, Transform *trans, float vx);
	void check_world_colission_vertical(Entity *ent, Transform *trans, float vy);

	bool is_out_of_bounds(int row, int col);

	void limit_to_bounds(Transform *trans);
};

#endif
