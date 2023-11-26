#include "InputSystem.h"
#include "../../Game.h"
#include "../EntityManager.h"
#include "../Components/Components.h"
#include "../../constants.h"

extern EntityManager g_entity_manager;

InputSystem::InputSystem()
{
	system_signature[static_cast<int>(ComponentType::TRANSFORM)] = true;
}

void InputSystem::update(float dt)
{
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT) {
			game->is_running = false;
			break;
		}
	}

	handle_key_down(dt);
	handle_key_up(dt);
}


void InputSystem::handle_key_down(float dt)
{

	std::list<Entity_ID>::iterator itr = entities.begin();
	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "InputSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_LEFT])
			trans->vel.x -= PLAYER_HORIZONTAL_ACCEL * dt;

		if(state[SDL_SCANCODE_RIGHT])
			trans->vel.x += PLAYER_HORIZONTAL_ACCEL * dt;

		if(state[SDL_SCANCODE_UP] && ent->is_on_ground == true)
		{
			trans->vel.y = PLAYER_JUMP_VEL;
			ent->is_on_ground = false;
		}

		itr++;
	}

}


void InputSystem::handle_key_up(float dt)
{
	std::list<Entity_ID>::iterator itr = entities.begin();
	while(itr != entities.end()) {
		Entity *ent = g_entity_manager.get_entity(*itr);

		if(ent == nullptr || ent->is_alive == false) {
			//std::cout << "InputSystem: deleted ID: " << *itr << std::endl;
			itr = entities.erase(itr);	
			continue;
		}

		Transform *trans = ent->get_component<Transform>(ComponentType::TRANSFORM);

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_LEFT] == 0 && state[SDL_SCANCODE_RIGHT] == 0) {
			if(trans->vel.x > 0) {
				trans->vel.x = trans->vel.x > IDLE_THRESHOLD ? trans->vel.x - (trans->friction * dt) : 0.0f;
			}
			else if(trans->vel.x < 0){
				trans->vel.x = trans->vel.x < -IDLE_THRESHOLD ? trans->vel.x + (trans->friction * dt) : 0.0f;
			}
		}
				
		itr++;
	}

}
