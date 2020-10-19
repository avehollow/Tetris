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


	b_Play = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Play->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 294, 322);
	b_Play->setTexture(AM_->texture[AM::E_TEXTURE::T_BPLAY]);
	b_Play->setHoveOverColor(sf::Color::White);
	b_Play->setFillColor(sf::Color(180, 180, 180));


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
			show_gui(true);
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
			show_gui(false);
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
	window->GUI_.erase((void*)b_Options);
	window->GUI_.erase((void*)b_Back);
	window->GUI_.erase((void*)b_Play);
}

void GAME::show_gui(bool show)
{
	b_Back->visible(show);
	b_Options->visible(show);
	b_Play->visible(show);
}
