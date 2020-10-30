#include "pch.h"
#include "Tetromino.h"


Tetromino::Tetromino()
{
}

void Tetromino::handleInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left  && !collision_with_edges(-1,0) && !collision_with_cubes(-1,0))
	{
		figure.move(-1, 0);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && !collision_with_edges(1, 0) && !collision_with_cubes(1, 0))
	{
		figure.move(1, 0);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !collision_with_edges(0, -1) && !collision_with_cubes(0, -1))
	{
		figure.move(0, -1);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !collision_with_edges(0, 1) && !collision_with_cubes(0, 1))
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

		figure.move(0, 0);
	}
}


void Tetromino::ini(int width, int height)
{
	rand_gen.seed(time(NULL));

	
	shift_interval = sf::seconds(1);
	shift_time = sf::seconds(0);
	shift_clock.restart();

	// AVE LOOK how to calculate element size
	cube_size = (CUBE_DIMENSIONS / 1080.0f) * window->getSize().y;
	cube_size_percent = cube_size / (float)window->getSize().y;


	WIDTH = width;
	HEIGHT = height;

	int xx = (window->getSize().x / 2) - (WIDTH / 2 * cube_size);
	int yy = (window->getSize().y / 2) - (HEIGHT / 2 * cube_size);
	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			tetromino[(WIDTH * y) + x].setPosition(xx + (x * cube_size), yy + (y * cube_size));
			tetromino[(WIDTH * y) + x].setSize(sf::Vector2f(cube_size, cube_size));
			//tetromino[(10 * y) + x].setFillColor(sf::Color::Transparent);
			tetromino[(WIDTH * y) + x].setTexture(&AM->texture[AM_::E_TEXTURE::T_CUBE_BLUE]);
			collisions[(WIDTH * y) + x] = 0;
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

	figure.ini(cube_size, AM, sf::Vector2f(xx, yy));

	figure.spawnFigure(
		background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
		background_tetromino.getPosition().y - 3 * cube_size,
		&AM->texture[AM_::E_TEXTURE::T_CUBE_GREEN],
		//E_FIGURE::I);
		E_FIGURE(rand_gen() % NUMBER_OF_FIGURES));
	
}


void Tetromino::onCreate()
{

	cube_size = window->getSize().y * cube_size_percent;
	
	int xx = (window->getSize().x / 2) - (WIDTH / 2 * cube_size);
	int yy = (window->getSize().y / 2) - (HEIGHT / 2 * cube_size);
	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			tetromino[(WIDTH * y) + x].setPosition(xx + (x * cube_size), yy + (y * cube_size));
			tetromino[(WIDTH * y) + x].setSize(sf::Vector2f(cube_size, cube_size));
		}
	}

	background_tetromino.setSize(sf::Vector2f(10 * cube_size, 20 * cube_size));
	background_tetromino.setPosition(xx, yy);

	LEFT_WALL = xx;
	RIGHT_WALL = xx + (WIDTH - 1) * cube_size;
	FLOOR_EDGE = yy + (HEIGHT - 1) * cube_size;

	figure.onCreate(cube_size, sf::Vector2f(xx, yy));

}


void Tetromino::update(const float& tt)
{
	shift_time += shift_clock.restart();
	if (shift_time >= shift_interval)
	{
		if (!collision_with_edges(0, 1) && !collision_with_cubes(0, 1))
		{
			figure.move(0, 1);
		}
		else
		{
			sf::Vector2i c1 = figure.indices[0];
			sf::Vector2i c2 = figure.indices[1];
			sf::Vector2i c3 = figure.indices[2];
			sf::Vector2i c4 = figure.indices[3];
		

			collisions[(WIDTH * c1.y ) + c1.x  ] = 1;
			collisions[(WIDTH * c2.y ) + c2.x  ] = 1;
			collisions[(WIDTH * c3.y ) + c3.x  ] = 1;
			collisions[(WIDTH * c4.y ) + c4.x  ] = 1;

			figure.spawnFigure(
				background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
				background_tetromino.getPosition().y - 3 * cube_size,
				&AM->texture[AM_::E_TEXTURE::T_CUBE_GREEN],
				//E_FIGURE::I);
				E_FIGURE(rand_gen() % NUMBER_OF_FIGURES));

		}
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

bool Tetromino::collision_with_cubes(float dir_x, float dir_y)
{
	sf::Vector2i c1 = figure.indices[0];
	sf::Vector2i c2 = figure.indices[1];
	sf::Vector2i c3 = figure.indices[2];
	sf::Vector2i c4 = figure.indices[3];
	float cs = figure.cube_size;

	if (collisions[(WIDTH * (c1.y + (int)dir_y)) + (c1.x + (int)dir_x)] || 
		collisions[(WIDTH * (c2.y + (int)dir_y)) + (c2.x + (int)dir_x)] ||
		collisions[(WIDTH * (c3.y + (int)dir_y)) + (c3.x + (int)dir_x)] || 
		collisions[(WIDTH * (c4.y + (int)dir_y)) + (c4.x + (int)dir_x)] 

		/*collisions[(HEIGHT * c1.y) + (c1.x + 1 )] ||
		collisions[(HEIGHT * c2.y) + (c2.x + 1 )] ||
		collisions[(HEIGHT * c3.y) + (c3.x + 1 )] ||
		collisions[(HEIGHT * c4.y) + (c4.x + 1 )] ||

		collisions[(HEIGHT * c1.y) + (c1.x - 1)] ||
		collisions[(HEIGHT * c2.y) + (c2.x - 1)] ||
		collisions[(HEIGHT * c3.y) + (c3.x - 1)] ||
		collisions[(HEIGHT * c4.y) + (c4.x - 1)] */
		)
	{
		return true;
	}

	return false;
}


