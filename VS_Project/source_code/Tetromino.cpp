#include "pch.h"
#include "Tetromino.h"
#include "GameWindow.h"

Tetromino::Tetromino(GameWindow* w)
	: window(w)
{
	
}

Tetromino::~Tetromino()
{
}

void Tetromino::draw() const
{
	window->draw(background_tetromino);
	for (size_t y = 0; y < 20; y++)
		for (size_t x = 0; x < 10; x++)
			window->draw(tetromino[(10 * y) + x]);
}

void Tetromino::ini(float SIZE_CUBE)
{
	float xx = (window->getSize().x / 2) - (5 * SIZE_CUBE);
	float yy = (window->getSize().y / 2) - (10 * SIZE_CUBE);
	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			tetromino[(10 * y) + x].setPosition(xx + (x * SIZE_CUBE), yy + (y * SIZE_CUBE));
			tetromino[(10 * y) + x].setSize(sf::Vector2f(SIZE_CUBE, SIZE_CUBE));
			//tetromino[(10 * y) + x].setFillColor(sf::Color::Transparent);
			tetromino[(10 * y) + x].setTexture(&am_.texture[AM::E_TEXTURE::T_CUBE_BLUE]);
		}
	}

	background_tetromino.setSize(sf::Vector2(10 * SIZE_CUBE, 20 * SIZE_CUBE));
	background_tetromino.setFillColor(sf::Color(20, 20, 20, 200));
	background_tetromino.setPosition(xx, yy);
	background_tetromino.setOutlineThickness(2);
	background_tetromino.setOutlineColor(sf::Color::White);

	LEFT_WALL = xx;
	RIGHT_WALL = xx + 9 * SIZE_CUBE;
	FLOOR_EDGE = yy + 19 * SIZE_CUBE;
}


void Tetromino::onCreate(float size_cube)
{
	float xx = (window->getSize().x / 2) - (5 * size_cube);
	float yy = (window->getSize().y / 2) - (10 * size_cube);

	background_tetromino.setSize(sf::Vector2(10 * size_cube, 20 * size_cube));
	background_tetromino.setPosition(xx, yy);

	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			tetromino[(10 * y) + x].setPosition(xx + (x * size_cube), yy + (y * size_cube));
			tetromino[(10 * y) + x].setSize(sf::Vector2f(size_cube, size_cube));
		}
	}

	LEFT_WALL = xx;
	RIGHT_WALL = xx + 10 * size_cube;
	FLOOR_EDGE = yy + 20 * size_cube;

}
