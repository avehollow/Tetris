#include "pch.h"
#include "MainMenu.h"
#include "Game.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "Button.h"

MAINMENU::MAINMENU(class GameWindow* w, AM* assetmanager)
	: window(w)
	, options(w, assetmanager)
	, AM_(assetmanager)
{
	//puts("CTOR MAINMENU");

	b_Exit = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, - b_Exit->getSize().x / 2, 126);
	b_Exit->setTexture(AM_->texture[AM::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_Options->getSize().x / 2, 234);
	b_Options->setTexture(AM_->texture[AM::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));

	b_NewGame = window->GUI_.CreateButton(0, 0, 318, 86);
	b_NewGame->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_NewGame->getSize().x / 2, 340);
	b_NewGame->setTexture(AM_->texture[AM::E_TEXTURE::T_BNEWGAME]);
	b_NewGame->setHoveOverColor(sf::Color::White);
	b_NewGame->setFillColor(sf::Color(180, 180, 180));
	
}

STATE* MAINMENU::handleInput(const sf::Event& event)
{
	STATE* s = nullptr;

	int result = 0;

	if (!substate.empty())
	{
		result = substate.top()->manageInput(event);
	}

	switch (result)
	{
	case RESULT::R_NONE:
		if (b_Exit->Pressed())
		{
			window->close();
		}
		if (b_NewGame->Pressed())
		{
			AM_->sound[AM::E_SOUND::S_CLICK_1].play();
			s = new GAME(window, AM_);
		}

		if (b_Options->Pressed())
		{
			show_gui(false);
			substate.push(&options);
			substate.top()->show();
		}
		break;
	case RESULT::B_BACK:
		substate.top()->hide();
		substate.pop();
		show_gui(true);

		break;
	default:
		break;
	}

	

    return s;
}

void MAINMENU::update(const float& d)
{
	if (!substate.empty())
	{
		substate.top()->update(d);
		return;
	}
}

void MAINMENU::render()const
{
	if (!substate.empty())
	{
		substate.top()->render();
	}
}

MAINMENU::~MAINMENU()
{
	//puts("Destruktor ~MAINMENU");

	window->GUI_.erase((void*)b_NewGame);
	window->GUI_.erase((void*)b_Options);
	window->GUI_.erase((void*)b_Exit);
}

void MAINMENU::show_gui(bool show)
{
	b_NewGame->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);
}
