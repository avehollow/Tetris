#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "Button.h"


GAME::GAME(GameWindow* w, AM* assetmanager)
	:  pause(w, assetmanager)
{
	//puts("CTOR Game");

	window = w;
	AM_ = assetmanager;

}

STATE* GAME::handleInput(const sf::Event& event)
{
	STATE* s = nullptr;

	if (!substates.empty())
	{
		substates.handleInput(event);

		if (pause.b_Exit->Pressed())
		{
			AM_->sound[AM::E_SOUND::S_CLICK_2].play();
			s = new MAINMENU(window, AM_);
		}
	}
	else
	{
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			substates.add(&pause);
		
	}
	

	return s;
}

void GAME::update(const float& d)
{

}

void GAME::render()const
{
	if (!substates.empty())
		substates.render();
}

GAME::~GAME()
{
	//puts("Destruktor ~Game");
}
