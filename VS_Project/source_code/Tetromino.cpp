#include "pch.h"
#include "Tetromino.h"
#include "assetmanager.h"
#include "GameWindow.h"

Tetromino::Tetromino(GameWindow* window, AM* assetmanager)
	: window(window)
	, am(assetmanager)
{

	shift_interval = sf::seconds(1);
	shift_time     = sf::seconds(0);


	// AVE LOOK how to calculate element size
	SIZE_CUBE = (CUBE_DIMENSIONS / 1080.0f) * window->getSize().y;
	SIZE_CUBE_PERCENT = SIZE_CUBE / (float)window->getSize().y;

	ini();
}

void Tetromino::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left  && !collision_with_edges(-1,0))
	{
		figure.move(-1, 0);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && !collision_with_edges(1, 0))
	{
		figure.move(1, 0);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !collision_with_edges(0, -1))
	{
		figure.move(0, -1);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !collision_with_edges(0, 1))
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
		if (!this->wall_kick())
		{
			figure.squares[0].setPosition(square1_before_rotation);
			figure.squares[1].setPosition(square2_before_rotation);
			figure.squares[2].setPosition(square3_before_rotation);
			figure.squares[3].setPosition(square4_before_rotation);
		}
	}
}


void Tetromino::ini(int width, int height)
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
	float xx = background_tetromino.getPosition().x;
	float yy = background_tetromino.getPosition().y;
	switch (type)
	{
	case I:
		figure.be_I_(xx, yy, texture);
		break;
	case L:
		figure.be_L_(xx, yy, texture);
		break;
	case T:
		figure.be_T_(xx, yy, texture);
		break;
	case Z:
		figure.be_Z_(xx, yy, texture);
		break;
	case O:
		figure.be_O_(xx, yy, texture);
		break;
	case LM:
		figure.be_LM_(xx, yy, texture);
		break;
	case ZM:
		figure.be_ZM_(xx, yy, texture);
		break;
	default:
		break;
	}
}

void Tetromino::restart()
{
	spawnFigure(background_tetromino.getPosition().x, background_tetromino.getPosition().y, &am->texture[AM::E_TEXTURE::T_CUBE_GREEN], E_FIGURE::I);
	for (size_t i = 0; i < 200; i++)
	{
		//tetromino[i].setFillColor(sf::Color::Transparent);
		collisions[i] = 0;
	}
}

void Tetromino::update(const float& tt)
{
	shift_time += shift_clock.restart();
	if (shift_time >= shift_interval)
	{
		figure.move(0,1);
		shift_time -= shift_interval;
	}
}

bool Tetromino::wall_kick()
{
	for (size_t i = 0; i < 2; i++)
	{
		// LEFT WALL
		if (figure.squares[0].getPosition().x < LEFT_WALL || figure.squares[1].getPosition().x < LEFT_WALL ||
			figure.squares[2].getPosition().x < LEFT_WALL || figure.squares[3].getPosition().x < LEFT_WALL)
		{
			// TODO Need check if wall kick is possible
			if (true)
			{
				figure.move(1,0);
			}
			else
			{
				// Wall kick is not possible
				return false;
			}


		}

		// RIGHT WALL
		else if (figure.squares[0].getPosition().x > RIGHT_WALL || figure.squares[1].getPosition().x > RIGHT_WALL ||
			figure.squares[2].getPosition().x > RIGHT_WALL || figure.squares[3].getPosition().x > RIGHT_WALL)
		{
			// TODO Need check if wall kick is possible
			if (true)
			{
				figure.move(-1, 0);
			}
			else
			{
				// Wall kick is not possible
				return false;
			}
		}

		// FLOOR
		else if (figure.squares[0].getPosition().y > FLOOR_EDGE || figure.squares[1].getPosition().y > FLOOR_EDGE ||
			figure.squares[2].getPosition().y > FLOOR_EDGE || figure.squares[3].getPosition().y > FLOOR_EDGE)
		{
			// TODO Need check if wall kick is possible
			if (true)
			{

				figure.move(0, -1);
			}
			else
			{
				// Wall kick is not possible
				return false;
			}
		}
	}

	return true;
}


bool Tetromino::collision_with_edges(float dir_x, float dir_y)
{

	if (figure.squares[0].getPosition().x + dir_x < LEFT_WALL || figure.squares[0].getPosition().x + dir_x > RIGHT_WALL ||
		figure.squares[0].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure.squares[1].getPosition().x + dir_x < LEFT_WALL || figure.squares[1].getPosition().x + dir_x > RIGHT_WALL ||
			figure.squares[1].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure.squares[2].getPosition().x + dir_x < LEFT_WALL || figure.squares[2].getPosition().x + dir_x > RIGHT_WALL ||
			figure.squares[2].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure.squares[3].getPosition().x + dir_x < LEFT_WALL || figure.squares[3].getPosition().x + dir_x > RIGHT_WALL ||
			figure.squares[3].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	return false;
}


