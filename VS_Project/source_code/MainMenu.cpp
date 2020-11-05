#include "pch.h"
#include "MainMenu.h"
#include "Button.h"
#include "Options.h"
#include "Game.h"

MAINMENU main_menu;
extern GAME game;
extern OPTIONS options;

MAINMENU::MAINMENU()
{
	//puts("CTOR MAINMENU");	
}

ISTATE* MAINMENU::handleInput(const sf::Event& event)
{
	ISTATE* state = this;

	if (b_NewGame->Pressed())
	{
		AM->sound[AM_::E_SOUND::S_CLICK_1].play();
		state = &game;
		game.setToPlay();;
	}
	else if (b_Exit->Pressed())
	{
		window->close();
	}
	else if (b_Options->Pressed())
	{
		state = &options;
	}

    return state;
}

void MAINMENU::update(const float& d)
{

}

void MAINMENU::render()const
{

	
}

void MAINMENU::show()
{
	show_gui(true);
}

void MAINMENU::hide()
{
	show_gui(false);
}

void MAINMENU::onCreate()
{
}

void MAINMENU::startUp()
{
	b_Exit = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_Exit->getSize().x / 2, 126);
	b_Exit->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_Options->getSize().x / 2, 234);
	b_Options->setTexture(AM->texture[AM_::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));

	b_NewGame = window->GUI_.CreateButton(0, 0, 318, 86);
	b_NewGame->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_NewGame->getSize().x / 2, 340);
	b_NewGame->setTexture(AM->texture[AM_::E_TEXTURE::T_BNEWGAME]);
	b_NewGame->setHoveOverColor(sf::Color::White);
	b_NewGame->setFillColor(sf::Color(180, 180, 180));

	options.startUp();
	game.startUp();
}

MAINMENU::~MAINMENU()
{
	//puts("Destruktor ~MAINMENU");
}


void MAINMENU::show_gui(bool show)
{
	b_NewGame->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);
}