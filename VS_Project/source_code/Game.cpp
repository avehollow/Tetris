#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "Button.h"

GAME::GAME(GameWindow* w, AM* assetmanager)
	: window(w)
	, options(w, assetmanager)
	, AM_(assetmanager)
	, substate(SUBSTATE::NONE)
{
	window->GUI_.clear();
	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 330, 214);
	b_Options->setTexture(AM_->texture[AM::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));

	b_Back = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 294, 106);
	b_Back->setTexture(AM_->texture[AM::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));


	//puts("CTOR Game");
}

STATE* GAME::handleInput(const sf::Event& event)
{
	STATE* s = nullptr;

	switch (substate)
	{
	case GAME::OPTIONS:
		if (options.manage_input(event) == RESULT::R_EXIT)
		{
			options.save();
			substate = SUBSTATE::NONE;
		}
		break;

	case GAME::NONE:
		if (b_Back->Pressed())
		{
			AM_->sound[AM::E_SOUND::S_CLICK_2].play();
			s = new MAINMENU(window, AM_);
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

void GAME::update(const float& d)
{
	switch (substate)
	{
	case GAME::OPTIONS:
		options.advance(d);
		break;

	case GAME::NONE:
		break;

	default:
		break;
	}
}

void GAME::render()const
{
	switch (substate)
	{
	case GAME::OPTIONS:
		options.display();
		break;

	case GAME::NONE:
		break;
;
	default:
		break;
	}
}

GAME::~GAME()
{
	//puts("Destruktor ~Game");
}
