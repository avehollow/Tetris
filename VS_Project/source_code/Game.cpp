#include "pch.h"
#include "Game.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "Button.h"


GAME::GAME(GameWindow* w, AM* assetmanager)
{
	//puts("CTOR Game");

	window = w;
	AM_ = assetmanager;
	isPause = false;

	window->addOnCreate(this);

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

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
	background_pause.setFillColor(sf::Color(55, 55, 55, 200));


	show_gui(false);


	background_game.setSize(sf::Vector2f(window->getSize()));
	background_game.setTexture(&AM_->texture[AM::E_TEXTURE::T_BACKGROUND_GAME]);

	// AVE LOOK how to calculate element size
	SIZE_CUBE = (CUBE_DIMENSIONS / 1080.0f) * window->getSize().y;

	SIZE_CUBE_PERCENT = SIZE_CUBE / window->getSize().y;


	float xx = (window->getSize().x / 2) - (5 * SIZE_CUBE);
	float yy = (window->getSize().y / 2) - (10 * SIZE_CUBE);
	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			tetromino[(10 * y) + x].setPosition(xx + (x * SIZE_CUBE), yy + (y * SIZE_CUBE));
			tetromino[(10 * y) + x].setSize(sf::Vector2f(SIZE_CUBE, SIZE_CUBE));
			tetromino[(10 * y) + x].setFillColor(sf::Color::Transparent);
		}
	}

	background_tetromino.setSize(sf::Vector2(10 * SIZE_CUBE, 20 * SIZE_CUBE));
	background_tetromino.setFillColor(sf::Color(20, 20, 20, 200));
	background_tetromino.setPosition(xx, yy);
	background_tetromino.setOutlineThickness(2);
	background_tetromino.setOutlineColor(sf::Color::White);
}

GAME::~GAME()
{
	//puts("Destruktor ~Game");
	window->GUI_.erase((void*)b_Options);
	window->GUI_.erase((void*)b_Back);
	window->GUI_.erase((void*)b_Exit);
}

E_STATE GAME::handleInput(const sf::Event& event)
{
	E_STATE s = E_STATE::ST_NONE;
	
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
			s = E_STATE::ST_OPTIONS;
		}
		else if (b_Exit->Pressed())
		{
			s = E_STATE::ST_BACK;
			isPause = false;
		}
	}
	else
	{

	}
		
	
	return s;
}


void GAME::update(const float& tt)
{

}

void GAME::render()const
{
	window->draw(background_game);

	window->draw(background_tetromino);
	for (size_t y = 0; y < 20; y++)
		for (size_t x = 0; x < 10; x++)
			window->draw(tetromino[(10 * y) + x]);
		
	
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
	sf::Vector2f size_cube{ window->getSize().y * SIZE_CUBE_PERCENT, window->getSize().y * SIZE_CUBE_PERCENT };
	float xx = (window->getSize().x / 2) - (5 * size_cube.x);
	float yy = (window->getSize().y / 2) - (10 * size_cube.y);
	

	background_tetromino.setSize(sf::Vector2(10 * size_cube.x, 20 * size_cube.x));
	background_tetromino.setPosition(xx, yy);


	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			tetromino[(10 * y) + x].setPosition(xx + (x * size_cube.x), yy + (y * size_cube.x));
			tetromino[(10 * y) + x].setSize(size_cube);
		}
	}



	background_game.setSize(sf::Vector2f(window->getSize()));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
}




