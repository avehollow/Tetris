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
	, substate(SUBSTATE::NONE)
{
	//puts("CTOR MAINMENU");
	window->GUI_.clear();
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

	switch (substate)
	{
	case MAINMENU::OPTIONS:
		if (options.manage_input(event) == RESULT::R_EXIT)
		{
			options.save();
			substate = SUBSTATE::NONE;
		}
		break;
	case MAINMENU::NONE:
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
			options.load();
			substate = SUBSTATE::OPTIONS;
		}
		break;
	default:
		break;
	}

	

    return s;
}

void MAINMENU::update(const float& d)
{
	switch (substate)
	{
	case MAINMENU::OPTIONS:
		options.advance(d);

		break;
	default:
		break;
	}
}

void MAINMENU::render()const
{
	switch (substate)
	{
	case MAINMENU::OPTIONS:
		options.display();

		break;
	default:
		break;
	}
	
}

MAINMENU::~MAINMENU()
{
	//puts("Destruktor ~MAINMENU");
}
