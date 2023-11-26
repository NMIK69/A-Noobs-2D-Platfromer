#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>

#include "Application.h"
#include "constants.h"
#include "ECS/ECS.h"


class Game
{
public:

	Game();
	~Game() = default;

	void update(float dt);
	void render();
	
	bool is_running{false};

private:
	InputSystem input_system;
	TransformSystem transform_system;
	RenderSystem render_system;
	AISystem ai_system;
	AnimationSystem animation_system;

	/* TODO: make list */
	std::vector<Entity_ID> enemy_ids;
	/* TODO: make list */
	std::list<Entity_ID> coin_ids;
	Entity_ID player_id;

	SDL_Texture *player_atlas;
	SDL_Texture *enemy_atlas;
	SDL_Texture *coin_atlas; 
	SDL_Texture *tile_atlas;
	SDL_Texture *win_msg;
	SDL_Texture *lose_msg;

	SDL_Rect camera;
	std::vector<std::vector<int>> map;

	enum GameState {WIN, LOSE, RUNNING, TERMINATED};
	GameState gamestate;


	std::vector<int> read_map_row(const std::string &str, char delim);
	std::vector<std::vector<int>> read_map_from_file(const char *filename);
	void create_map(const std::vector<std::vector<int>> &map);
	
	void init_enemies();
	void init_player();

	void update_camera();
	void check_coin_collision();
	void check_enemy_collision();

	void update_gamestate();
	void display_win();
	void display_lose();
};

#endif
