#pragma once

#include "player.h"
#include "sound.h"

#include <iostream>
#include<Windows.h>
#include <SDL_mixer.h>

Player::Player(std::string id)
	: Game_Object(id, "My_Char_Idle")
{
	_speed = 0.1f;

	

	_translation = Vector_2D(0, 0);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::Idle);
}

Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Player::setDead(bool a)
{
	isDead = a;
}

void Player::simulate_AI(Uint32, Assets* assets, Input* input, Scene*)
{
	switch(_state.top())
	{
		case State::Idle:
			if (!isDead) {
			if(input->is_button_state(Input::Button::JUMPING, Input::Button_State::PRESSED))
			{
				push_state(State::Jumping, assets);
			}
			else if(_velocity.magnitude() > 0.0f)
			{
				push_state(State::Walking, assets);
			}
			}
			else if(health>0)
			{
				push_state(State::Hit, assets);
				setDead(false);
			}
			else
			{
				push_state(State::Dead, assets);
			}
			break;
			break;
		case State::Walking:
			if (!isDead) {
				if (_velocity.magnitude() == 0.0f  )
				{
					push_state(State::Idle, assets);
				}
				else if (input->is_button_state(Input::Button::JUMPING, Input::Button_State::PRESSED))
				{
					push_state(State::Jumping, assets);
				}
			}
			else if (health > 0)
			{
				push_state(State::Hit, assets);
			
				setDead(false);
			}
			else
			{
				push_state(State::Dead, assets);
			}
			break;
		case State::Jumping:
		
			 if(input->is_button_state(Input::Button::JUMPING, Input::Button_State::RELEASED))
			{
				push_state(State::Idle, assets);
			}
			if(_velocity.magnitude() != 0.0f)
			{
				push_state(State::Walking, assets);
			}
			break;
		case State::Hit:
			health--;
			push_state(State::Hit, assets);
				if (_velocity.magnitude() == 0.0f)
				{
					push_state(State::Idle, assets);
				}
				else if (_velocity.magnitude() > 0.0f)
				{
					push_state(State::Walking, assets);
				}
				else if (input->is_button_state(Input::Button::JUMPING, Input::Button_State::PRESSED))
				{
					push_state(State::Jumping, assets);
				}
				
	
			break;

	
		
			break;
	}

	_velocity = Vector_2D(0, 0);

	if(input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{	
		_velocity += Vector_2D(1.0f, 0);
	}

	if(input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-1.0f, 0);
	}

	if(input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -1.0f);
	}

	if(input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 1.0f);
	}

	_velocity.normalize();
	_velocity.scale(_speed);
}

void Player::set_speed(float speed)
{
	_speed = speed;
}
float Player::speed()
{
	return _speed;
}

void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}
void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets)
{

	switch(state)
	{
		case State::Idle:
		{
			_texture_id = "My_Char_Idle";
			_speed = 0.15f;
			const int attacking_channel = 4;
			Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
			Mix_PlayChannel(attacking_channel, sound->data(), -1);
			break; 
		}
		case State::Walking:
		{
			_texture_id = "My_Char_Walking";
			_speed = 0.15f;
			const int walking_channel =2;
			Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
			Mix_PlayChannel(walking_channel, sound->data(), -1);
			break;
		}
		case State::Jumping:
		{
			_texture_id = "My_Char_jumping";
			_speed = 0.1f;
			const int jumping_channel = 3;
			Sound* sound = (Sound*)assets->get_asset("Sound.jumping");
			Mix_PlayChannel(jumping_channel, sound->data(), -1);
			break;
		}
		case State::Hit:
		{
			_texture_id = "My_Char_Hit";
			_speed = 0.15f;
			const int dying_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.attacking");
			Mix_PlayChannel(dying_channel, sound->data(), -1);
			Sleep(90);
			break;
		}
		case State::Dead:
		{
			_texture_id = "My_Char_Dead";
			_speed = 0.3f;
			const int Dead_channel = 5;
		
			break;
		}
	}
}

void Player::handle_exit_state(State state, Assets*)
{
	switch(state)
	{
	case State::Idle: 
	    {
		    const int attacking_channel = 4;
		    Mix_HaltChannel(attacking_channel);
		    break; 
	    }
		case State::Walking:
		{
			const int walking_channel = 2;
			Mix_HaltChannel(walking_channel);
			break;
		}
		case State::Jumping:
		{
			const int jumping_channel = 3;
			Mix_HaltChannel(jumping_channel);
			break;
		}
		case State::Hit:
		{
			const int dying_channel = 1;
			Mix_HaltChannel(dying_channel);
			break;
		}
		case State::Dead:
		{
			const int dying_channel = 5;
		
			break;
		}
	}
}