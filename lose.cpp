#pragma once

#include "Lose.h"
#include "scene.h"
#include "player.h"
#include "game_object.h"
#include "assets.h"

Lose::Lose()
	: Game_Object("lose", "lose")
{
	_width = 600;
	_height = 600;
	_translation = Vector_2D(100, 100);
	// float a = rand() % 50 + 0.1f;
	 //_velocity = Vector_2D(11.0f, 0);

	//_velocity += Vector_2D(-0.2f, 0);

	//_velocity.normalize();
	//_velocity.scale(0.1f);
}

Lose::~Lose()
{

}
void Lose::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}


void Lose::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	scene->get_game_objects();

}


