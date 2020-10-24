#include "pch.h"
#include "Game.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "Button.h"


GAME::GAME(GameWindow* w, AM* assetmanager)
	: tetromino(w,assetmanager)
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
	SIZE_CUBE_PERCENT = SIZE_CUBE / (float)window->getSize().y;

	tetromino.ini(SIZE_CUBE);
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
		tetromino.handleInput(event);
	}
		
	
	return s;
}


void GAME::update(const float& tt)
{
	
}

void GAME::render()const
{
	window->draw(background_game);

	window->draw(tetromino);

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


//
//bool GAME::collision_with_edges(float dir_x, float dir_y)
//{
//
//	if (figure.squares[0].getPosition().x + dir_x < tetromino.LEFT_WALL || figure.squares[0].getPosition().x + dir_x > tetromino.RIGHT_WALL ||
//		figure.squares[0].getPosition().y + dir_y > tetromino.FLOOR_EDGE)
//	{
//		return true;
//	}
//
//	else if (figure.squares[1].getPosition().x + dir_x < tetromino.LEFT_WALL || figure.squares[1].getPosition().x + dir_x > tetromino.RIGHT_WALL ||
//			figure.squares[1].getPosition().y + dir_y > tetromino.FLOOR_EDGE)
//	{
//		return true;
//	}
//
//	else if (figure.squares[2].getPosition().x + dir_x < tetromino.LEFT_WALL || figure.squares[2].getPosition().x + dir_x > tetromino.RIGHT_WALL ||
//			figure.squares[2].getPosition().y + dir_y > tetromino.FLOOR_EDGE)
//	{
//		return true;
//	}
//
//	else if (figure.squares[3].getPosition().x + dir_x < tetromino.LEFT_WALL || figure.squares[3].getPosition().x + dir_x > tetromino.RIGHT_WALL ||
//			figure.squares[3].getPosition().y + dir_y > tetromino.FLOOR_EDGE)
//	{
//		return true;
//	}
//
//	return false;
//}

//bool GAME::collision_with_cubes(float dir_x, float dir_y)
//{
//
//	// [ (20*y) + x]
//	
//
//	return false;
//}
//
//bool GAME::check_collision(float dir_x, float dir_y)
//{
//
//
//	return collision_with_edges(dir_x, dir_y) || collision_with_cubes(dir_x, dir_y);
//}
//
//bool GAME::wall_kick()
//{
//	for (size_t i = 0; i < 2; i++)
//	{
//		// LEFT WALL
//		if (figure.squares[0].getPosition().x < tetromino.LEFT_WALL || figure.squares[1].getPosition().x < tetromino.LEFT_WALL ||
//			figure.squares[2].getPosition().x < tetromino.LEFT_WALL || figure.squares[3].getPosition().x < tetromino.LEFT_WALL)
//		{
//			// TODO Need check if wall kick is possible
//			if (true)
//			{
//				figure.move(SIZE_CUBE,0);
//			}
//			else
//			{
//				// Wall kick is not possible
//				return false;
//			}
//
//
//		}
//
//		// RIGHT WALL
//		else if (figure.squares[0].getPosition().x > tetromino.RIGHT_WALL || figure.squares[1].getPosition().x > tetromino.RIGHT_WALL ||
//			figure.squares[2].getPosition().x > tetromino.RIGHT_WALL || figure.squares[3].getPosition().x > tetromino.RIGHT_WALL)
//		{
//			// TODO Need check if wall kick is possible
//			if (true)
//			{
//				figure.move(-SIZE_CUBE, 0);
//			}
//			else
//			{
//				// Wall kick is not possible
//				return false;
//			}
//		}
//
//		// FLOOR
//		else if (figure.squares[0].getPosition().y > tetromino.FLOOR_EDGE || figure.squares[1].getPosition().y > tetromino.FLOOR_EDGE ||
//			figure.squares[2].getPosition().y > tetromino.FLOOR_EDGE || figure.squares[3].getPosition().y > tetromino.FLOOR_EDGE)
//		{
//			// TODO Need check if wall kick is possible
//			if (true)
//			{
//
//				figure.move(0 ,-SIZE_CUBE);
//			}
//			else
//			{
//				// Wall kick is not possible
//				return false;
//			}
//		}
//	}
//
//	return true;
//}



void GAME::onCreate()
{

	sf::Vector2f size_cube{ window->getSize().y * SIZE_CUBE_PERCENT, window->getSize().y * SIZE_CUBE_PERCENT };
	SIZE_CUBE = size_cube.x;

	tetromino.onCreate(size_cube.x);

	background_game.setSize(sf::Vector2f(window->getSize()));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
}




