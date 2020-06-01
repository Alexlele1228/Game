#pragma once

#include "game_object.h"
#include <vector>

class Area : public Game_Object
{
public:
	Area(Vector_2D);
	~Area();
	std::vector<std::string>list = {"a"};
	bool hitAlready(std::string);
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;
	
};