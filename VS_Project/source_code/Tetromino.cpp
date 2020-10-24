#include "pch.h"
#include "Tetromino.h"
#include "assetmanager.h"
#include "GameWindow.h"

Tetromino::Tetromino(GameWindow* window, AM* assetmanager)
	: window(window)
	, am(assetmanager)
{
}

void Tetromino::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left )
	{
		figure.move(-1, 0);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
	{
		figure.move(1, 0);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
	{
		figure.move(0, -1);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down )
	{
		figure.move(0, 1);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		////
		//   When function WallKick() return false
		//		 Get the postion of the squares before rotation :)
		sf::Vector2f square1_before_rotation = figure.squares[0].getPosition();
		sf::Vector2f square2_before_rotation = figure.squares[1].getPosition();
		sf::Vector2f square3_before_rotation = figure.squares[2].getPosition();
		sf::Vector2f square4_before_rotation = figure.squares[3].getPosition();
		figure.rotate();

		// Wall kick is not possible
		/*if (!this->wall_kick())
		{
			figure.squares[0].setPosition(square1_before_rotation);
			figure.squares[1].setPosition(square2_before_rotation);
			figure.squares[2].setPosition(square3_before_rotation);
			figure.squares[3].setPosition(square4_before_rotation);
		}*/
	}
}


void Tetromino::ini(int cube_size, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;

	int xx = (window->getSize().x / 2) - (WIDTH / 2 * cube_size);
	int yy = (window->getSize().y / 2) - (HEIGHT / 2 * cube_size);
	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			tetromino[(10 * y) + x].setPosition(xx + (x * cube_size), yy + (y * cube_size));
			tetromino[(10 * y) + x].setSize(sf::Vector2f(cube_size, cube_size));
			//tetromino[(10 * y) + x].setFillColor(sf::Color::Transparent);
			tetromino[(10 * y) + x].setTexture(&am->texture[AM::E_TEXTURE::T_CUBE_BLUE]);
		}
	}

	background_tetromino.setSize(sf::Vector2f(10 * cube_size, 20 * cube_size));
	background_tetromino.setFillColor(sf::Color(20, 20, 20, 200));

	background_tetromino.setPosition(xx, yy);
	background_tetromino.setOutlineThickness(2);
	background_tetromino.setOutlineColor(sf::Color::White);

	LEFT_WALL = xx;
	RIGHT_WALL = xx + (WIDTH - 1) * cube_size;
	FLOOR_EDGE = yy + (HEIGHT - 1) * cube_size;

	figure.ini(cube_size, am, sf::Vector2f(xx, yy));
}


void Tetromino::onCreate(int cube_size)
{
	this->ini(cube_size, WIDTH, HEIGHT);

	int xx = (window->getSize().x / 2) - (WIDTH / 2 * cube_size);
	int yy = (window->getSize().y / 2) - (HEIGHT / 2 * cube_size);
	figure.onCreate(cube_size, sf::Vector2f(xx, yy));
}

void Tetromino::spawnFigure(float pos_x, float pos_y, sf::Texture* texture, E_FIGURE type)
{

}


