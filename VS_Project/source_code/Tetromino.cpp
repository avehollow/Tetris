#include "pch.h"
#include "Tetromino.h"




void Tetromino::handleInput(const sf::Event& event)
{
	if (tetris)
	{
		return;
	}

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
		pause();
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
	{
		xyz = !xyz;
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
		sf::Vector2f center_before_rotation = figure.center_pos;
		figure.rotate();
		
		if (collision_with_cubes(0,0))
		{
			if (!elo())
			{
				figure.squares[0].setPosition(square1_before_rotation);
				figure.squares[1].setPosition(square2_before_rotation);
				figure.squares[2].setPosition(square3_before_rotation);
				figure.squares[3].setPosition(square4_before_rotation);
				figure.center_pos = center_before_rotation;
			}
			pause();
		}

		// Wall kick is not possible
		if (!this->wall_kick())
		{
			figure.squares[0].setPosition(square1_before_rotation);
			figure.squares[1].setPosition(square2_before_rotation);
			figure.squares[2].setPosition(square3_before_rotation);
			figure.squares[3].setPosition(square4_before_rotation);
			figure.center_pos = center_before_rotation;
		}
		figure.move(0, 0);

	}

	
}


void Tetromino::ini(int width, int height)
{
	//view = window->getDefaultView();
	//view.zoom(1.5);
	//window->setView(view);

	tetris_row.resize(height + 4, -1);

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
			tetromino[(WIDTH * y) + x].setFillColor(sf::Color::Transparent);
		}
	}	
	
	for (size_t y = 0; y < HEIGHT + 4; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
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
	CEIL_EDGE = yy;

	figure.ini(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));


	figure.spawnFigure(
		background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
		background_tetromino.getPosition().y - 2 * cube_size,
		&AM->texture[AM_::E_TEXTURE::T_CUBE_GREEN],
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

	background_tetromino.setSize(sf::Vector2f(WIDTH * cube_size, HEIGHT * cube_size));
	background_tetromino.setPosition(xx, yy);

	LEFT_WALL = xx;
	RIGHT_WALL = xx + (WIDTH - 1) * cube_size;
	FLOOR_EDGE = yy + (HEIGHT - 1) * cube_size;
	CEIL_EDGE = yy;

	figure.onCreate(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));

}

void Tetromino::check_tetris()
{

 	int yes = 0;
	for (int y = 0; y < HEIGHT + 4; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			yes += collisions[(WIDTH * y) + x];
		
		
		if (yes == WIDTH)
		{
			for (int x = 0; x < WIDTH; x++)
				collisions[(WIDTH * y) + x] = 0;

			tetris_row[y] = y;
			tetris = true;
		}
			yes = 0;
	}
	
}

void Tetromino::play_anim_tetris()
{
	static int n = 0;
	for (auto& y : tetris_row)
	{
		if (y != -1)
		{
			tetromino[(WIDTH * (y - 4)) + (WIDTH/2) + at].setFillColor(sf::Color::Transparent);
			// AVE LOOK problem with unusual size of tetromino
			tetromino[(WIDTH * (y - 4)) + (WIDTH/2) - (at+1)].setFillColor(sf::Color::Transparent);
			n++;
		}
	}
	if (at++; at == WIDTH / 2)
	{
		n = 0;
		at = 0;
		for (auto& y : tetris_row)
			y = -1;
	}
	if (n) 
	{
		for (size_t y = 0; y < HEIGHT; y++)
		{
			for (size_t x = 0; x < WIDTH; x++)
			{
				tetromino[(WIDTH * y) + x].setPosition(xx + (x * cube_size), yy + (y * cube_size));
				tetromino[(WIDTH * y) + x].setSize(sf::Vector2f(cube_size, cube_size));
				tetromino[(WIDTH * y) + x].setFillColor(sf::Color::Transparent);
			}
		}

		for (int y = HEIGHT + 4 - 1; y >= 0; y--)
		{
			for (int x = WIDTH - 1; x >= 0 ; x--)
			{
				collisions[(WIDTH * y) + x] = collisions[(WIDTH * (y + 1)) + x];
				collisions[(WIDTH * (y + 1)) + x] = 0;
			}
		}
		n--;
	}
}


void Tetromino::update(const float& tt)
{
	

	shift_time += shift_clock.restart();
	if (shift_time >= shift_interval)
	{
		if (tetris)
		{
			play_anim_tetris();
		}
		else if (!collision_with_edges(0, 1) && !collision_with_cubes(0, 1))
		{
			figure.move(0, 1);
		}
		else
		{

			sf::Vector2i c1 = figure.indices[0];
			sf::Vector2i c2 = figure.indices[1];
			sf::Vector2i c3 = figure.indices[2];
			sf::Vector2i c4 = figure.indices[3];
		
			if (!xyz)
			{
				collisions[(WIDTH * c1.y ) + c1.x  ] = 1;
				collisions[(WIDTH * c2.y ) + c2.x  ] = 1;
				collisions[(WIDTH * c3.y ) + c3.x  ] = 1;
				collisions[(WIDTH * c4.y ) + c4.x  ] = 1;

				tetromino[(WIDTH * (c1.y-4) ) + c1.x  ].setTexture(figure.squares[0].getTexture());
				tetromino[(WIDTH * (c2.y-4) ) + c2.x  ].setTexture(figure.squares[1].getTexture());
				tetromino[(WIDTH * (c3.y-4) ) + c3.x  ].setTexture(figure.squares[2].getTexture());
				tetromino[(WIDTH * (c4.y-4) ) + c4.x  ].setTexture(figure.squares[3].getTexture());

				tetromino[(WIDTH * (c1.y - 4)) + c1.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c2.y - 4)) + c2.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c3.y - 4)) + c3.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c4.y - 4)) + c4.x].setFillColor(sf::Color::White);

			}
			
			figure.spawnFigure(
				background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
				background_tetromino.getPosition().y - 2 * cube_size,
				&AM->texture[AM_::E_TEXTURE::T_CUBE_GREEN],
				E_FIGURE(rand_gen() % NUMBER_OF_FIGURES));

			check_tetris();

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
			if (!collision_with_cubes(1,0))
			{
				figure.move(1,0);
			}
			else
			{
				figure.move(1,0);
				if (!collision_with_cubes(1, 0))
				{
					figure.move(1, 0);
					return true;
				}

				if (!collision_with_cubes(2, 0))
				{
					figure.move(2, 0);
					return true;
				}
				// Wall kick is not possible
				return false;
			}


		}

		// RIGHT WALL
		else if (figure.squares[0].getPosition().x > RIGHT_WALL || figure.squares[1].getPosition().x > RIGHT_WALL ||
			figure.squares[2].getPosition().x > RIGHT_WALL || figure.squares[3].getPosition().x > RIGHT_WALL)
		{
			// TODO Need check if wall kick is possible
			if (!collision_with_cubes(-1, 0))
			{
				figure.move(-1, 0);
			}
			else
			{
				figure.move(-1, 0);
				if (!collision_with_cubes(-1, 0))
				{
					figure.move(-1, 0);
					return true;
				}

				if (!collision_with_cubes(-2, 0))
				{
					figure.move(-2, 0);
					return true;
				}
				// Wall kick is not possible
				return false;
			}
		}

		// FLOOR
		else if (figure.squares[0].getPosition().y > FLOOR_EDGE || figure.squares[1].getPosition().y > FLOOR_EDGE ||
			figure.squares[2].getPosition().y > FLOOR_EDGE || figure.squares[3].getPosition().y > FLOOR_EDGE)
		{
			// TODO Need check if wall kick is possible
			if (!collision_with_cubes(0, -1))
			{

				figure.move(0, -1);
			}
			else
			{
				figure.move(0, -1);

				if (!collision_with_cubes(0, -1))
				{
					figure.move(0, -1);
					return true;
				}

				if (!collision_with_cubes(0, -2))
				{
					figure.move(0, -2);
					return true;
				}
		
				// Wall kick is not possible
				return false;
				
			}
		}
	}
	pause();
	return true;
}


bool Tetromino::collision_with_edges(int dir_x, int dir_y)
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

bool Tetromino::collision_with_cubes(int dir_x, int dir_y)
{

	sf::Vector2i c1 = figure.indices[0];
	sf::Vector2i c2 = figure.indices[1];
	sf::Vector2i c3 = figure.indices[2];
	sf::Vector2i c4 = figure.indices[3];


	if (collisions[(WIDTH * (c1.y + (int)dir_y)) + (c1.x + (int)dir_x)] || 
		collisions[(WIDTH * (c2.y + (int)dir_y)) + (c2.x + (int)dir_x)] ||
		collisions[(WIDTH * (c3.y + (int)dir_y)) + (c3.x + (int)dir_x)] || 
		collisions[(WIDTH * (c4.y + (int)dir_y)) + (c4.x + (int)dir_x)] 
		)
	{
		return true;
	}

	return false;
}

bool Tetromino::elo()
{
	if (!collision_with_cubes(1,0))
	{
		figure.move(1, 0);
		return true;
	}

	if (!collision_with_cubes(2, 0))
	{
		figure.move(2, 0);
		return true;
	}

	if (!collision_with_cubes(-1,0))
	{
		figure.move(-1, 0);
		return true;
	}

	if (!collision_with_cubes(-2, 0))
	{
		figure.move(-2, 0);
		return true;
	}

	if (!collision_with_cubes(0, -1))
	{
		figure.move(0, -1);
		return true;
	}

	if (!collision_with_cubes(0, -2))
	{
		figure.move(0, -2);
		return true;
	}
	return false;
}


