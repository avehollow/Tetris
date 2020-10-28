#include "pch.h"
#include "PDA.h"
#include "GameWindow.h"
#include "assetmanager.h"

PDA::PDA(class GameWindow* w, class AM* am)
{
	data_states_[E_STATE::ST_MAINMENU] = new MAINMENU(w, am);
	data_states_[E_STATE::ST_GAME] = new GAME(w, am);
	data_states_[E_STATE::ST_OPTIONS] = new OPTIONS(w, am);
	states_.push(data_states_[E_STATE::ST_MAINMENU]);
}

PDA::~PDA()
{
	for (auto& st : data_states_)
	{
		delete st;
	}
}

void PDA::handleInput(const sf::Event& event)
{
	/*if (states_.empty())
		return;*/

	E_STATE nstate = states_.top()->handleInput(event);
	if (nstate == E_STATE::ST_NONE)
	{
		// do nothing
	}
	else if (nstate == E_STATE::ST_BACK)
	{
		states_.top()->hide();
		states_.pop();

		//if (!states_.empty())
			states_.top()->show();
			if (nstate == E_STATE::ST_GAME)
			{
				// states_.top()->ini();
			}
	}
	else
	{
		states_.top()->hide();
		states_.push(st_ptrs[nstate]);
		states_.top()->show();
	}
}

void PDA::update(float dt) const
{
	//if(!states_.empty())
		states_.top()->update(dt);
}

void PDA::render() const
{
	//if(!states_.empty())
		states_.top()->render();
}
