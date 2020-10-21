#include "pch.h"
#include "PDA.h"
#include "GameWindow.h"
#include "assetmanager.h"

PDA::PDA(class GameWindow* w, class AM* am)
	: main_menu(w, am)
	, game(w, am)
	, options(w, am)
{
	states_.push(&main_menu);
}

PDA::~PDA()
{
	
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
