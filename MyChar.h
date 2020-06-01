#pragma once

#include "game_object.h"

class MyChar : public Game_Object
{
public:
	MyChar(std::string id);
	~MyChar();
	

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};