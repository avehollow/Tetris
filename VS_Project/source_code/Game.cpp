#include "pch.h"
#include "Game.h"
#include "MainMenu.h"
#include "assetmanager.h"

GAME::GAME(sf::RenderWindow* w, AM* assetmanager)
	: window(w)
	, options(w, assetmanager)
	, AM_(assetmanager)
	, substate(SUBSTATE::NONE)
{
	const size_t SIZE = (sizeof(menu) / sizeof(sf::Text));
	for (size_t i = 0; i < SIZE; i++)
	{
		menu[i].setFont(AM_->font[AM::E_FONT::F_NINEPIN]);
		menu[i].setString("--");
		menu[i].setFillColor(sf::Color::Magenta);
		menu[i].setCharacterSize(25);
		menu[i].setStyle(sf::Text::Style::Italic);
		menu[i].setPosition(w->getSize().x * 0.85, w->getSize().y * (0.05 + (0.05 * i)));
	}
	menu[MENUTX::M_MAINMENU].setString("Main Menu");
	menu[MENUTX::M_OPTIONS].setString("Options");
	menu[MENUTX::M_EXIT].setString("EXIT");

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
		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left
			&& menu[MENUTX::M_EXIT].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			window->close();
		}

		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left
			&& menu[MENUTX::M_MAINMENU].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			AM_->sound[AM::E_SOUND::S_CLICK_2].play();
			s = new MAINMENU(window, AM_);
		}

		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left
			&& menu[MENUTX::M_OPTIONS].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
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
		for (auto& tx : menu)
		{
			if (tx.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
				tx.setFillColor(sf::Color::Blue);
			else
				tx.setFillColor(sf::Color::Magenta);
		}
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
		for (const auto& el : menu)
			window->draw(el);
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
