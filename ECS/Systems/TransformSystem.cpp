#include "TransformSystem.h" 
#include "../EntityManager.h"
#include "../../constants.h"


extern EntityManager g_entity_manager;

TransformSystem::TransformSystem()
{
	system_signature[static_cast<int>(ComponentType::TRANSFORM)] = true;
}

void TransformSystem::update(float dt)
{

	std::list<Entity_ID>::iterator itr = entities.begin();
	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "TransformSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);

		trans->vel.y += trans->grav.y * dt;

		trans->vel.y = std::max(std::min(trans->vel.y, MAX_VEL_Y), MIN_VEL_Y);
		trans->vel.x = std::max(std::min(trans->vel.x, MAX_VEL_X), MIN_VEL_X);

		trans->pos.x += trans->vel.x;
		check_world_colission_horizontal(ent, trans, trans->vel.x);
		
		trans->pos.y += trans->vel.y;
		check_world_colission_vertical(ent, trans, trans->vel.y);
		
		limit_to_bounds(trans);

		itr++;
	}
}


void TransformSystem::limit_to_bounds(Transform *trans)
{
	if(trans->pos.y > map_pixel_height - TILE_SIZE) {
		trans->pos.y = map_height - TILE_SIZE;
		trans->vel.y = 0;
	}
	if(trans->pos.y < 0) {
		trans->pos.y = 0;
		trans->vel.y = 0;
	}
	if(trans->pos.x > map_pixel_width - TILE_SIZE) {
		trans->pos.x = map_width - TILE_SIZE;
		trans->vel.x = 0;
	}
	if(trans->pos.x < 0) {
		trans->pos.x = 0;
		trans->vel.x = 0;
	}
}

void TransformSystem::set_world_map(const std::vector<std::vector<int>> &map)
{
	world_map = map;
	map_height = map.size();
	map_pixel_height = map_height * TILE_SIZE;
	assert(map_height > 0);
	map_width = map[0].size();
	map_pixel_width = map_width * TILE_SIZE;
	assert(map_width > 0);
}

bool TransformSystem::is_out_of_bounds(int row, int col)
{
	if(row < 0 || row >= map_pixel_height ||
	   col < 0 || col >= map_pixel_width) {
	   	return true;
	}
	return false;
}

/* source for the collision logic with the world map: https://www.parallelrealities.co.uk/tutorials/ppp/ppp3.php */
void TransformSystem::check_world_colission_horizontal(Entity *ent, Transform *trans, float vx)
{

	(void) ent;
	if(vx == 0) return;
	

	/* Calculate the column of the tile we intersected in the world map
	 * based on the direction we traveled. This is either the left or the
	 * right side of our character hitbox. */
	int mx = vx > 0 ? (trans->pos.x + TILE_SIZE) : trans->pos.x;
	mx /= TILE_SIZE;

	/* Calculate the row of the intersected tile in the world map.
	 * We first look at the tile we intersect with the
	 * top of our character hitbox. So based on if we moved left or right,
	 * we either look at the top right or top left corner. */
	int my = trans->pos.y / TILE_SIZE;

	bool colission = false;
	/* check for intersection with a collidable tile */
	if(is_out_of_bounds(my, mx) || (world_map[my][mx] != 0 && world_map[my][mx] != 3)) {
		colission = true;
	}

	/* now we set the row to a new value. */
	/* this time we look at the bottom of our 
	   character hitbox rectangle */
	/* we also subtract 1. */
	/* if we would not subtract 1 we would have jerky movement
	   when walking on a tile, since we would permanently insersect
	   and colide with it */
	my = (trans->pos.y + TILE_SIZE - 1) / TILE_SIZE;

	/* check for intersection with a collidable tile */
	if(is_out_of_bounds(my, mx) || (world_map[my][mx] != 0 && world_map[my][mx] != 3)) {
		colission = true;
	}

	if(colission == true) {
		/* if we moved to the right, we want to set our
		   position to the left of the intersected tile*/
		/* if we moved to the left we want to set our position
		   to right of the intersected tile */
		int adjustment = vx > 0 ? -TILE_SIZE : TILE_SIZE;

		/* calculate the position */
		trans->pos.x = (mx * TILE_SIZE) + adjustment;

		/* recomended, or else you would not lose speed 
		   when colliding with the world */
		trans->vel.x = 0;
	}
}

/* same logic as for the horizontal world colission but for the y velocity */
void TransformSystem::check_world_colission_vertical(Entity *ent, Transform *trans, float vy) 
{
	if(vy == 0) return;


	int my = vy > 0 ? (trans->pos.y + TILE_SIZE) : trans->pos.y;
	my /= TILE_SIZE;

	int mx = trans->pos.x / TILE_SIZE;

	bool colission = false;
	if (is_out_of_bounds(my, mx) || (world_map[my][mx] != 0 && world_map[my][mx] != 3)) {
		colission = true;
	}


	mx = (trans->pos.x + TILE_SIZE - 1) / TILE_SIZE;


	if (is_out_of_bounds(my, mx) || (world_map[my][mx] != 0 && world_map[my][mx] != 3)) {
		colission = true;
	}

	if (colission == true) {
		int adjustment = vy > 0 ? -TILE_SIZE : TILE_SIZE;

		trans->pos.y = (my * TILE_SIZE) + adjustment;

		trans->vel.y = 0;

		ent->is_on_ground = vy > 0;
	}
}
