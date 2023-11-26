#ifndef GAME_ENTITY_H 
#define GAME_ENTITY_H

#include <iostream>
#include <assert.h>
#include <bitset>
#include <array>

#include "../common.h"
#include "Components/Components.h"


class Entity
{
public:
	
	Entity()
	: is_alive{true}, components{}, component_signature{0}
	{
	}

	/* call all the destructurs of components */
	~Entity()
	{
		for(std::size_t i = 0; i < components.size(); i++) {
			delete components[i];
		}
	}


	void print_info() {
		std::cout << "Group Sign: ";
		for(int i = 0; i < static_cast<int>(ComponentType::MAX_COMPONENT_TYPES); i++) {
			std::cout << component_signature[i] << " ";
		}
		std::cout << std::endl;
		
		std::cout << "Component type: ";
		for(int i = 0; i < static_cast<int>(ComponentType::MAX_COMPONENT_TYPES); i++) {
			if(components[i] != nullptr) {
				std::cout  << static_cast<int>(components[i]->type) << " ";
			}
			else std::cout << "NULL ";
		}
		std::cout << std::endl;
	}

	
	template <typename T>
	//void add_component(const T &comp) {
	void add_component(T &&comp) {
		static_assert(std::is_base_of<Component, T>::value);
		assert(comp.type != ComponentType::INVALID_TYPE);	

		int type_index = static_cast<int>(comp.type);
		assert(component_signature[type_index] == false);

		T *temp = new T{std::move(comp)};

		component_signature[type_index] = true;
		components[type_index] = temp;
	}


	void remove_component(ComponentType type)
	{
		int type_index = static_cast<int>(type);	
		if(component_signature[type_index] == false) {
			std::cerr << "Entity has no component to remove" << std::endl;	
			return;
		}

		delete components[type_index];
		components[type_index] = nullptr;

		component_signature[type_index] = false;
	}


	/* TODO: maybe return a reference? */
	template<typename T>
	T *get_component(ComponentType type)
	{
		static_assert(std::is_base_of<Component, T>::value);

		int type_index = static_cast<int>(type);	

		if(component_signature[type_index] == false) return nullptr;

		return static_cast<T*>(components[type_index]);
	}

	
	const Signature& get_signature() const
	{
		return component_signature;
	}


	bool is_alive{true};
	bool is_on_ground{true};

private:
	/* the actual components */
	std::array<Component*, static_cast<int>(ComponentType::MAX_COMPONENT_TYPES)> components;

	/* a unique signature of
	   all the components the entity is made out of */
	Signature component_signature;
};

#endif
