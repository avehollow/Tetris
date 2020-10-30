#include "pch.h"
#include "Game.h"
#include "Button.h"
#include "Options.h"

GAME game;


extern OPTIONS options;

GAME::GAME()
{
	//puts("CTOR Game");
}

GAME::~GAME()
{
	//puts("Destruktor ~Game");
	window->GUI_.erase((void*)b_Options);
	window->GUI_.erase((void*)b_Back);
	window->GUI_.erase((void*)b_Exit);
}

STATE* GAME::handleInput(const sf::Event& event)
{
	STATE* state = this;
	
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
	{
		isPause = !isPause;
		show_gui(isPause);
	}
	else if (isPause)
	{
		if (b_Back->Pressed() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
		{
			isPause = false;
			show_gui(false);
		}
		else if (b_Options->Pressed())
		{
			state = &options;
		}
		else if (b_Exit->Pressed())
		{
			state = nullptr;
			isPause = false;
		}
	}
	else
	{
		tetromino.handleInput(event);
	}
		
	
	return state;
}


void GAME::update(const float& tt)
{
	if (!isPause)
	{
		tetromino.update(tt);
	}
	else
	{
		tetromino.pause();
	}
}

void GAME::render()const
{
	window->draw(background_game);

	tetromino.draw(window);

	if (isPause)
		window->draw(background_pause);
	
}

void GAME::show()
{
	show_gui(isPause);
}

void GAME::hide()
{
	show_gui(false);
}

void GAME::show_gui(bool show)
{
	b_Back->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);
}



void GAME::onCreate()
{
	tetromino.onCreate();

	background_game.setSize(sf::Vector2f(window->getSize()));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
}

void GAME::startUp()
{
	isPause = false;

	window->addOnCreate(this);

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER, -159, -143);
	b_Options->setTexture(AM->texture[AM_::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));


	b_Back = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 43);
	b_Back->setTexture(AM->texture[AM_::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));

	b_Exit = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 143);
	b_Exit->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
	background_pause.setFillColor(sf::Color(55, 55, 55, 200));

	show_gui(false);

	background_game.setSize(sf::Vector2f(window->getSize()));
	background_game.setTexture(&AM->texture[AM_::E_TEXTURE::T_BACKGROUND_GAME]);

}

void GAME::setToPlay()
{
	tetromino.ini();
}




