#pragma once

#include "Area.h"
#include "scene.h"
#include "player.h"
#include "game_object.h"
#include "assets.h"

Area::Area(Vector_2D a)
	: Game_Object("rocks", "rocks")
{
	_width  = 50;
	_height = 50;
	_translation = a;
   // float a = rand() % 50 + 0.1f;
	//_velocity = Vector_2D(11.0f, 0);
	
	_velocity += Vector_2D(-0.2f, 0);

	_velocity.normalize();
	_velocity.scale(0.1f);
}

Area::~Area()
{

}
void Area::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Area::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	Game_Object* MyChar = scene->get_game_object("MyChar");
	

	Vector_2D Area_center = _translation 
									+ Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = MyChar->translation()
									+ Vector_2D((float)MyChar->width() / 2, (float)MyChar->height() / 2);

	float distance_to_player = (Area_center - player_center).magnitude();

	
	Player* player = (Player*)scene->get_game_object("MyChar");
	std::string id=this->id();

	
	if(distance_to_player<50.0f && !hitAlready(id))
	{
		
		list.push_back(id);
		player->setDead(true);
		
		
		
	}


}

bool Area::hitAlready(std::string a) {
	for (int i = 0; i < list.size(); i++) {
		if (a == list.at(i))
			return true;
		
	}
	return false;
}