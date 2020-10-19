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
{

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER, -159, -143); 
	b_Options->setTexture(AM_->texture[AM::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));


	b_Back = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 43); 
	b_Back->setTexture(AM_->texture[AM::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));

	b_Exit = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 143);
	b_Exit->setTexture(AM_->texture[AM::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	pause_background.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	pause_background.setPosition(window->getSize().x / 2 - pause_background.getSize().x / 2, window->getSize().y / 2 - pause_background.getSize().y / 2);
	pause_background.setFillColor(sf::Color(55, 55, 55, 200));


	show_gui(false);
	//puts("CTOR Game");
}

STATE* GAME::handleInput(const sf::Event& event)
{
	STATE* s = nullptr;
	int result = 0;


	if (!substate.empty())
		result = substate.top()->manageInput(event);
	

	switch (result)
	{
	case RESULT::R_NONE:
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			show_gui(true);

		else if (b_Back->Pressed())
			show_gui(false);
		
		else if (b_Options->Pressed())
		{
			show_gui(false);
			substate.push(&options);
			substate.top()->show();
		}
		else if (b_Exit->Pressed())
		{
			AM_->sound[AM::E_SOUND::S_CLICK_2].play();
			s = new MAINMENU(window, AM_);
		}

		break;

	case RESULT::B_BACK:
		substate.top()->hide();
		substate.pop();

		break;

	case RESULT::B_EXIT:
	
		break;

	default:
		break;
	}
	
	return s;
}

void GAME::update(const float& d)
{
	if (!substate.empty())
	{
		substate.top()->update(d);
		return;
	}
}

void GAME::render()const
{
	if (!substate.empty())
		substate.top()->render();
	
}

GAME::~GAME()
{
	//puts("Destruktor ~Game");
	window->GUI_.erase((void*)b_Options);
	window->GUI_.erase((void*)b_Back);
	window->GUI_.erase((void*)b_Exit);
}

void GAME::show_gui(bool show)
{
	b_Back->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);
}
