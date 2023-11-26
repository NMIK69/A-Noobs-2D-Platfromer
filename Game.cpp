#include <SDL2/SDL_image.h>

#include "Game.h"
#include "animation_scripts.h"
#include "ai_scripts.h"


EntityManager g_entity_manager;


Game::Game()
: is_running{true},
  player_atlas {IMG_LoadTexture(Application::renderer,"assets/player_atlas.png")},
  enemy_atlas {IMG_LoadTexture(Application::renderer,"assets/enemy_atlas.png")},
  coin_atlas {IMG_LoadTexture(Application::renderer, "assets/coin_atlas.png")},
  tile_atlas {IMG_LoadTexture(Application::renderer, "assets/tile_atlas.png")},
  win_msg {IMG_LoadTexture(Application::renderer, "assets/you_win.png")},
  lose_msg {IMG_LoadTexture(Application::renderer, "assets/you_lose.png")},
  camera{0,0,Application::window_width, Application::window_height},
  gamestate{RUNNING}

{
	input_system.game = this;
	render_system.set_camera(&camera);
	
	map = read_map_from_file("map.txt"); 
	create_map(map);

	transform_system.set_world_map(map);
	
	init_enemies();
	init_player();
}

void Game::update_gamestate()
{
	Entity *player = g_entity_manager.get_entity(player_id);
	if(player == nullptr || player->is_alive == false)
		gamestate = LOSE;

	if(coin_ids.size() == 0)
		gamestate = WIN;
}

void Game::display_win()
{
	SDL_Rect src{0,0,400,256};
	SDL_Rect dest{200,128,400,256};
	SDL_RenderCopy(Application::renderer, win_msg, &src, &dest);	
}

void Game::display_lose()
{
	SDL_Rect src{0,0,400,256};
	SDL_Rect dest{200,128,400,256};
	SDL_RenderCopy(Application::renderer, lose_msg, &src, &dest);	
}

void Game::update(float dt)
{
	update_camera();	

	input_system.update(dt);

	if(gamestate != RUNNING) return;

	transform_system.update(dt);

	ai_system.update();

	check_coin_collision();

	check_enemy_collision();

	render_system.update();
	
	animation_system.update(dt);

	update_gamestate();
}

void Game::render()
{
	SDL_RenderClear(Application::renderer);

	render_system.render();
	if(gamestate == WIN)
		display_win();
	if(gamestate == LOSE)
		display_lose();

	SDL_RenderPresent(Application::renderer);
}


void Game::init_player()
{
	float ground_level = (map.size() -2) * TILE_SIZE;

	player_id = g_entity_manager.create_entity();
	Entity *player = g_entity_manager.get_entity(player_id);

	player->add_component<Transform>(Transform{160, ground_level, 18, 25.0f});
	player->add_component<Sprite>(Sprite{0,0,TILE_SIZE,TILE_SIZE,100,100,player_atlas});
	player->add_component<Animation>(Animation{player_animation});

	transform_system.add_entity(player_id);
	input_system.add_entity(player_id);
	render_system.add_entity(player_id);
	animation_system.add_entity(player_id);

}

/* ugly but good enough for now */
void Game::init_enemies()
{
	float ground_level = (map.size() -2) * TILE_SIZE;

	std::vector<std::vector<float>> enemy_spawns{{17,22,2}, {44,47,1}};
	for (std::size_t i = 0; i < enemy_spawns.size(); i++) {
		Entity_ID temp = g_entity_manager.create_entity();
		enemy_ids.push_back(temp);
		Entity *enemy = g_entity_manager.get_entity(temp);
		
		/* ground level spawn point */
		float start_x = (enemy_spawns[i][0] * TILE_SIZE) + 10;
		float end_x = (enemy_spawns[i][1] * TILE_SIZE) - 10;

		enemy->add_component<Transform>(Transform{start_x, ground_level, 1, 1, enemy_spawns[i][2]});
		enemy->add_component<Sprite>(Sprite{0,0,TILE_SIZE,TILE_SIZE,0,0,enemy_atlas});
		enemy->add_component<AI>(AI{vertical_enemy_movment, {start_x, 0}, {end_x, 0}});
		enemy->add_component<Animation>(Animation{enemy_animation});

		transform_system.add_entity(temp);
		render_system.add_entity(temp);
		ai_system.add_entity(temp);
		animation_system.add_entity(temp);
	}
}

std::vector<int> Game::read_map_row(const std::string &str, char delim) 
{
    std::vector<int> row;
    std::stringstream ss{str};
    std::string temp;

    while (getline(ss, temp, delim)) {
        row.push_back(atoi(temp.c_str()));
    }

    return row;
}

std::vector<std::vector<int>> Game::read_map_from_file(const char *filename)
{
	std::vector<std::vector<int>> map;

	std::ifstream ifs{filename, std::ifstream::in};
	while(ifs) {
		std::string temp;
		std::getline(ifs, temp, '\n');
		if(temp.size() != 0) {
			std::vector<int> row = read_map_row(temp, ',');
			map.push_back(row);
		}
	}

	ifs.close();		

	return map;
}

/* TODO: this function also creates the coins in the world.
         maybe seperate these two? make an extra create_coin()
	 function ???? */
void Game::create_map(const std::vector<std::vector<int>> &map)
{
	for(std::size_t i = 0; i < map.size(); i++) {
		for(std::size_t j = 0; j < map[i].size(); j++) {
			float y = i * TILE_HEIGHT;	
			float x = j * TILE_WIDTH;
			
			if(map[i][j] == 0) {
				Entity_ID id = g_entity_manager.create_entity();
				Entity *ent = g_entity_manager.get_entity(id);

				ent->add_component<Sprite>(Sprite{0,0,TILE_SIZE,TILE_SIZE,0,0,tile_atlas});
				ent->add_component<Transform>(Transform{x,y});

				render_system.add_entity(id);
			}

			else if(map[i][j] == 1){
				Entity_ID id = g_entity_manager.create_entity();
				Entity *ent = g_entity_manager.get_entity(id);

				ent->add_component<Sprite>(Sprite{TILE_SIZE,0,TILE_SIZE,TILE_SIZE,0,0,tile_atlas});
				ent->add_component<Transform>(Transform{x,y});

				render_system.add_entity(id);
			}

			else if(map[i][j] == 2){
				Entity_ID id = g_entity_manager.create_entity();
				Entity *ent = g_entity_manager.get_entity(id);

				ent->add_component<Sprite>(Sprite{64,0,TILE_SIZE,TILE_SIZE,0,0,tile_atlas});
				ent->add_component<Transform>(Transform{x,y});

				render_system.add_entity(id);
			}


			if(map[i][j] == 3){
				/* coin background */
				Entity_ID bg_id = g_entity_manager.create_entity();
				Entity *bg_ent = g_entity_manager.get_entity(bg_id);

				bg_ent->add_component<Sprite>(Sprite{0,0,TILE_SIZE,TILE_SIZE,0,0,tile_atlas});
				bg_ent->add_component<Transform>(Transform{x,y});

				render_system.add_entity(bg_id);

				/* actual coin */
				Entity_ID coin_id = g_entity_manager.create_entity();
				Entity *coin_ent = g_entity_manager.get_entity(coin_id);
				coin_ent->add_component<Sprite>(Sprite{0,0,TILE_SIZE,TILE_SIZE,0,0,coin_atlas});
				coin_ent->add_component<Transform>(Transform{x,y});
				coin_ent->add_component<Animation>(Animation{coin_animation});
				coin_ids.push_back(coin_id);

				render_system.add_entity(coin_id);
				animation_system.add_entity(coin_id);
			}
		}
	}
}

void Game::update_camera()
{
	int map_height = map.size();
	assert(map_height > 0);
	int map_width = map[0].size();

	Entity *player = g_entity_manager.get_entity(player_id);
	Transform *pt = player->get_component<Transform>(ComponentType::TRANSFORM);

	camera.x = pt->pos.x - (camera.w/2);
	camera.y = pt->pos.y - (camera.h/2);
	/* TODO: change to max x and max y */
	int max_cam_x = (TILE_SIZE * map_width) - camera.w;
	int max_cam_y = (TILE_SIZE * map_height) - camera.h;
	if(camera.x < 0) camera.x = 0;
	if(camera.y < 0) camera.y = 0;
	if(camera.x > max_cam_x) camera.x = max_cam_x;
	if(camera.y > max_cam_y) camera.y = max_cam_y;
}

void Game::check_coin_collision()
{
	Entity *player = g_entity_manager.get_entity(player_id);
	Transform *pt = player->get_component<Transform>(ComponentType::TRANSFORM);

	std::list<Entity_ID>::iterator itr = coin_ids.begin();
	while(itr != coin_ids.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			itr = coin_ids.erase(itr);	
			continue;
		}

		Transform *ct = ent->get_component<Transform>(ComponentType::TRANSFORM);
		if(has_overlap(pt->pos.x, pt->pos.y, TILE_SIZE, TILE_SIZE,
			ct->pos.x, ct->pos.y, TILE_SIZE, TILE_SIZE) == true) {
			ent->is_alive = false;
			g_entity_manager.delete_entity(*itr);
		}

		itr++;
	}
}

void Game::check_enemy_collision()
{
	Entity *player = g_entity_manager.get_entity(player_id);
	Transform *pt = player->get_component<Transform>(ComponentType::TRANSFORM);

	for(std::size_t i = 0; i < enemy_ids.size(); i++) {
		Entity *enemy = g_entity_manager.get_entity(enemy_ids[i]); 
		if(enemy == nullptr || enemy->is_alive == false) continue;

		Transform *et = enemy->get_component<Transform>(ComponentType::TRANSFORM);
		if(has_overlap(pt->pos.x, pt->pos.y, TILE_SIZE, TILE_SIZE, 
		               et->pos.x, et->pos.y, TILE_SIZE, TILE_SIZE)) {
			       //enemy->is_alive = false;
			       player->is_alive = false;
			       //g_entity_manager.delete_entity(player_id);
			       //g_entity_manager.delete_entity(enemy_ids[i]);
		}
	}
}
