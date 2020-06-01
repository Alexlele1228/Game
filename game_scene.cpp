#include "game_scene.h"
#include "MyChar.h"
#include "player.h"
#include "Area.h"
#include "Lose.h"
#include "Win.h"
#include <vector>
#include <Windows.h>
#include<time.h>
#include<stdio.h>
#include<String>
using namespace std;

Game_Scene::Game_Scene()
	: Scene("Game")
{

	counter = 0;
	Game_Object* MyChar = new Player("MyChar");
	_game_objects[MyChar->id()] = MyChar;



}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{

	string a =to_string(++counter);
	
	if (this->get_game_object("MyChar")->health > 0 && frames<2500) {
		float b = rand() % 800 + 0.1f;
		if (timer == 0) {
			Game_Object* area1 = new Area(Vector_2D(800, b));
			_game_objects[a] = area1;

		}

		timer += 0.1f;
		if (timer > 1.5)
			timer = 0;
		frames++;
	}
	else if(frames>=2500&& this->get_game_object("MyChar")->health > 0)
	{
		Game_Object* win = new Win();
		_game_objects["win"] = win;

	}
	else {
		this->get_game_object("MyChar")->setTextureId("My_Char_Dead");
		Game_Object* lose = new Lose();
		_game_objects["lose"] = lose;

		
	}
	
}

