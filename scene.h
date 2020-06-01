#pragma once

#include <map>
#include <string>
#include <vector>

#include <SDL.h>

class Game_Object;

class Scene
{
public:
	Scene(std::string id);
	~Scene();

	virtual void update(SDL_Window* window) = 0;

	Game_Object* get_game_object(std::string id);
	std::vector<Game_Object*> get_game_objects();

	std::string id();

protected:
	std::map<std::string, Game_Object*> _game_objects;
	std::string                         _id;
};