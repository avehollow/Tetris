#include "pch.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "Options.h"
GAME game;

extern OPTIONS options;

ISTATE* GAME::handleInput(const sf::Event& event)
{
	ISTATE* state = this;
	
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
	{
		bPause = !bPause;
		show_gui(bPause);
	}
	else if (bPause)
	{
		if (b_Back->Pressed() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
		{
			bPause = false;
			show_gui(false);
			tetromino.pause();
		}
		else if (b_Options->Pressed())
		{
			state = &options;
		}
		else if (b_Exit->Pressed())
		{
			state = nullptr;
			bPause = false;
		}
	}
	else if (bGameOver)
	{

	}
	else
	{
		tetromino.handleInput(event);
	}
		
	
	return state;
}


void GAME::update(const float& tt)
{
	if (!bPause)
	{
		bGameOver = score = tetromino.update(tt);
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

	if (bPause)
	{
		window->draw(background_pause);
	}
	else if (bGameOver)
	{
		window->draw(background_gameover);
		window->draw(txGameOver);
		window->draw(txScore);
		window->draw(txDate);
	}
}

void GAME::show()
{
	show_gui(bPause);
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
	bPause = false;
	bGameOver = false;
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

	background_gameover.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	background_gameover.setPosition(window->getSize().x / 2 - background_gameover.getSize().x / 2, window->getSize().y / 2 - background_gameover.getSize().y / 2);
	background_gameover.setFillColor(sf::Color(30, 30, 30, 200));

	txb_Nick = window->GUI_.CreateTextBox(0,0, 200, 40, 1, "Enter your name");
	txb_Nick->setRelativePosition(gui::E_ANCHOR::A_CENTER, -200, -100);
	txb_Nick->setBoxStyle(1);
	txb_Nick->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	txb_Nick->setCharacterSize(25);
	txb_Nick->setFillColor(sf::Color::White);
	//txb_Nick->setActiveColor();

	b_Exit2 = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit2->setRelativePosition(gui::E_ANCHOR::A_CENTER, 124, 143);
	b_Exit2->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit2->setHoveOverColor(sf::Color::White);
	b_Exit2->setFillColor(sf::Color(180, 180, 180));
	
	b_PlayAgain = window->GUI_.CreateButton(0, 0, 248, 86);
	b_PlayAgain->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 143);
	b_PlayAgain->setTexture(AM->texture[AM_::E_TEXTURE::T_BPLAY]);
	b_PlayAgain->setHoveOverColor(sf::Color::White);
	b_PlayAgain->setFillColor(sf::Color(180, 180, 180));

}

void GAME::setToPlay()
{
	tetromino.ini();
}




