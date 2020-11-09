#include "pch.h"
#include "Tetromino.h"

// > 100
#define SCORE_FACTOR 300

void Tetromino::handleInput(const sf::Event& event)
{
	(this->*curr_hdl_fun)(event);
}


void Tetromino::ini(int width, int height)
{
	
	view = window->getDefaultView();
	view.zoom(1.5);
	//window->setView(view);

	tetris_row.resize(height + 4, -1);
	for (auto& k : tetris_row)
		k = -1;
	
	rand_gen.seed(rd());

	
	shift_interval = sf::milliseconds(1000);
	shift_time = sf::milliseconds(0);
	shift_clock.restart();
	score = 0;

	// AVE LOOK how to calculate element size
	cube_size = (CUBE_DIMENSIONS / 1080.0f) * window->getSize().y;
	cube_size_percent = cube_size / (float)window->getSize().y;


	WIDTH = width;
	HEIGHT = height;


	for (size_t y = 0; y < HEIGHT; y++)
	{
		for (size_t x = 0; x < WIDTH; x++)
		{
			tetromino[(WIDTH * y) + x].setFillColor(sf::Color::Transparent);
			collisions[(WIDTH * (y + 4)) + x] = 0;
		}
	}	
	
	for (size_t y = 0; y <  4; y++)
		for (size_t x = 0; x < WIDTH; x++)
			collisions[(WIDTH * y) + x] = 0;
		
	

	background_tetromino.setFillColor(sf::Color(20, 20, 20, 200));
	background_tetromino.setOutlineThickness(2);
	background_tetromino.setOutlineColor(sf::Color::White);
	
	background_score.setFillColor(sf::Color(20, 20, 20, 200));
	background_score.setOutlineThickness(2);
	background_score.setOutlineColor(sf::Color::White);	

	background_next.setFillColor(sf::Color(20, 20, 20, 200));
	background_next.setOutlineThickness(2);
	background_next.setOutlineColor(sf::Color::White);


	txNext.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txNext.setString("Next");

	txScore.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txScore.setString("Score");
	
	txNumScore.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);

	this->onCreate();

	figure.ini(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));
	place_holder.ini(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));
	place_holder.setTexture(&AM->texture[AM_::E_TEXTURE::T_CUBE_PLACEHOLDER]);

	place_holder.squares[0].setFillColor(sf::Color(place_holder.squares[0].getFillColor().r, place_holder.squares[0].getFillColor().g, place_holder.squares[0].getFillColor().b, 140));
	place_holder.squares[1].setFillColor(sf::Color(place_holder.squares[1].getFillColor().r, place_holder.squares[1].getFillColor().g, place_holder.squares[1].getFillColor().b, 140));
	place_holder.squares[2].setFillColor(sf::Color(place_holder.squares[2].getFillColor().r, place_holder.squares[2].getFillColor().g, place_holder.squares[2].getFillColor().b, 140));
	place_holder.squares[3].setFillColor(sf::Color(place_holder.squares[3].getFillColor().r, place_holder.squares[3].getFillColor().g, place_holder.squares[3].getFillColor().b, 140));

	for (int i = 0; i < 3; i++)
	{
		nextFigures[i].ini(cube_size, sf::Vector2f(0, 0));

		nextFigures[i].spawnFigure(
			background_next.getPosition().x,
			background_next.getPosition().y + cube_size * (4 * i + 1),
			&AM->texture[(rand_gen() % 7) + 8],
			E_FIGURE(rand_gen() % NUMBER_OF_FIGURES),
			rand_gen() % 4);
	}

	figure.spawnFigure(
		background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
		background_tetromino.getPosition().y - 3 * cube_size,
		&AM->texture[(rand_gen() % 7) + 8],
		E_FIGURE(rand_gen() % NUMBER_OF_FIGURES),
		rand_gen() % 4);

	update_placeholder();
	bGameOver = false;
	
	curr_hdl_fun = &Tetromino::standard_input;
	curr_upd_fun = &Tetromino::tick;
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


	int endTetrominoX = xx + (WIDTH * cube_size);
	
	background_score.setSize(sf::Vector2f(10 * cube_size, 1 * cube_size));
	background_score.setPosition(
		endTetrominoX + (((window->getSize().x - endTetrominoX) / 2) - (background_score.getSize().x / 2)),
		yy + 18 * cube_size);


	background_next.setSize(sf::Vector2f(4 * cube_size, 12 * cube_size));
	background_next.setPosition(
		endTetrominoX + (((window->getSize().x - endTetrominoX) / 2) - (background_next.getSize().x / 2)),
		yy + 3 * cube_size);


	txNext.setCharacterSize(cube_size);
	txNext.setPosition(
		endTetrominoX + (((window->getSize().x - endTetrominoX) / 2) - (txNext.getGlobalBounds().width / 2))
		, background_next.getPosition().y - cube_size - 3);


	txScore.setCharacterSize(cube_size);
	txScore.setPosition(
		endTetrominoX + (((window->getSize().x - endTetrominoX) / 2) - (txScore.getGlobalBounds().width / 2))
		, background_score.getPosition().y - cube_size - 3);


	LEFT_WALL = xx;
	RIGHT_WALL = xx + (WIDTH - 1) * cube_size;
	FLOOR_EDGE = yy + (HEIGHT - 1) * cube_size;
	CEIL_EDGE = yy;

	update_score(0);

	figure.onCreate(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));

	for (int i = 0; i < 3; i++)
	{
		nextFigures[i].ini(cube_size, sf::Vector2f(0, 0));

		nextFigures[i].spawnFigure(
			background_next.getPosition().x,
			background_next.getPosition().y + cube_size * (4 * i + 1),
			nextFigures[i].getTexture(),
			nextFigures[i].type,
			nextFigures[i].rotation);
	}
	place_holder.ini(cube_size, sf::Vector2f(LEFT_WALL, CEIL_EDGE - 4 * cube_size));
	update_placeholder();
}

void Tetromino::update_score(size_t pointsToAdd)
{
	score += pointsToAdd;
	txNumScore.setString(std::to_string(score));
	txNumScore.setOrigin(txNumScore.getLocalBounds().left, txNumScore.getLocalBounds().top);

	txNumScore.setPosition(
		background_score.getPosition().x + background_score.getSize().x / 2 - txNumScore.getGlobalBounds().width / 2,
		background_score.getPosition().y + background_score.getSize().y / 2 - txNumScore.getGlobalBounds().height / 2
	);
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
	/*		for (int x = 0; x < WIDTH; x++)
				collisions[(WIDTH * y) + x] = 0;*/

			tetris_row[y] = y;
			curr_upd_fun = &Tetromino::play_anim_tetris;
			curr_hdl_fun = &Tetromino::disable_input;
			numT++;
		}
			yes = 0;
	}
}

void Tetromino::play_anim_tetris(const float& tt)
{

	static int at = 0;
	for (auto& y : tetris_row)
	{
		if (y != -1)
		{
			collisions[(WIDTH * y) + at] = 0;
			collisions[(WIDTH * y) + at+5] = 0;

			tetromino[(WIDTH * (y - 4)) + (WIDTH/2) + at].setFillColor(sf::Color::Transparent);
			// AVE LOOK problem with unusual size of tetromino
			tetromino[(WIDTH * (y - 4)) + (WIDTH/2) - (at+1)].setFillColor(sf::Color::Transparent);
			update_score((at + 2) * SCORE_FACTOR);
		}
	}
	if (at++; at == WIDTH / 2)
	{
		at = 0;
		curr_upd_fun = &Tetromino::shift_tetris;
	}

}


void Tetromino::shift_tetris(const float& tt)
{
	/*for (int row = 5, size  = tetris_row.size(); row < size ; row++)
	{
		for (int y = row; (tetris_row[row] != -1) && (y >= 5); y--)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				tetromino[(WIDTH * (y - 4)) + x].setTexture(tetromino[(WIDTH * (y - 5)) + x].getTexture());
				tetromino[(WIDTH * (y - 4)) + x].setFillColor(tetromino[(WIDTH * (y - 5)) + x].getFillColor());
				collisions[(WIDTH * (y) + x)] = collisions[(WIDTH * (y - 1) + x)]; 
			}
		}
	}

	for (int x = 0; x < WIDTH; x++)
		tetromino[x].setFillColor(sf::Color::Transparent);
	
	for (auto& y : tetris_row)
		y = -1;
	curr_upd_fun = &Tetromino::tick;
	curr_hdl_fun = &Tetromino::standard_input;*/


	for (int y = HEIGHT - 2; y >= 0; y--)
	{
		int a = 0;
		for (int x = 0; x < WIDTH; x++)
		{
			a += collisions[(WIDTH * (y + 5)) + x];
		}

		if (!a)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				tetromino[(WIDTH * (y + 1)) + x].setTexture(tetromino[(WIDTH * y) + x].getTexture());
				tetromino[(WIDTH * (y + 1)) + x].setFillColor(tetromino[(WIDTH * y) + x].getFillColor());
				collisions[(WIDTH * (y + 5)) + x] = collisions[(WIDTH * (y + 4)) + x];
				collisions[(WIDTH * (y + 4)) + x] = 0;
			}
		}
	}

	for (size_t x = 0; x < WIDTH; x++)
		tetromino[x].setFillColor(sf::Color::Transparent);	


	if (numT--; numT == 0)
	{
		for (auto& y : tetris_row)
			y = -1;

		curr_upd_fun = &Tetromino::tick;
		curr_hdl_fun = &Tetromino::standard_input;
	}
	update_placeholder();
	
}



void Tetromino::tick(const float& tt)
{
	if (!collision_with_edges(0, 1, &figure) && !collision_with_cubes(0, 1, &figure))
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
			if (c1.y < 4 || c2.y < 4 || c3.y < 4 || c4.y < 4)
			{
				bGameOver = true;
				return;
			}
			else
			{
				collisions[(WIDTH * c1.y) + c1.x] = 1;
				collisions[(WIDTH * c2.y) + c2.x] = 1;
				collisions[(WIDTH * c3.y) + c3.x] = 1;
				collisions[(WIDTH * c4.y) + c4.x] = 1;

				tetromino[(WIDTH * (c1.y - 4)) + c1.x].setTexture(figure.squares[0].getTexture());
				tetromino[(WIDTH * (c2.y - 4)) + c2.x].setTexture(figure.squares[1].getTexture());
				tetromino[(WIDTH * (c3.y - 4)) + c3.x].setTexture(figure.squares[2].getTexture());
				tetromino[(WIDTH * (c4.y - 4)) + c4.x].setTexture(figure.squares[3].getTexture());

				tetromino[(WIDTH * (c1.y - 4)) + c1.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c2.y - 4)) + c2.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c3.y - 4)) + c3.x].setFillColor(sf::Color::White);
				tetromino[(WIDTH * (c4.y - 4)) + c4.x].setFillColor(sf::Color::White);
			}

		}

		if (shift_interval > sf::milliseconds(200))
			shift_interval -= sf::milliseconds(5);
		else
		{ 
			std::cout << "200!!!\n";
		}

		update_score(100);
		spawn_figure();
		check_tetris();
	}
	update_placeholder();
}

void Tetromino::standard_input(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && !collision_with_edges(-1, 0, &figure) && !collision_with_cubes(-1, 0, &figure))
	{
		figure.move(-1, 0);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && !collision_with_edges(1, 0, &figure) && !collision_with_cubes(1, 0, &figure))
	{
		figure.move(1, 0);
	}

	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !collision_with_edges(0, -1, &figure) && !collision_with_cubes(0, -1, &figure))
	{
		figure.move(0, -1);
	}

	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !collision_with_edges(0, 1, &figure) && !collision_with_cubes(0, 1, &figure))
	{
		figure.move(0, 1);
		update_score(SCORE_FACTOR * 0.01);
		pause();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
	{
		xyz = !xyz;
	}

	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
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

		if (collision_with_cubes(0, 0, &figure))
		{
			if (!elo())
			{
				figure.squares[0].setPosition(square1_before_rotation);
				figure.squares[1].setPosition(square2_before_rotation);
				figure.squares[2].setPosition(square3_before_rotation);
				figure.squares[3].setPosition(square4_before_rotation);
				figure.center_pos = center_before_rotation;
			}
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
		pause();
	}
	update_placeholder();
}

void Tetromino::disable_input(const sf::Event& event)
{
	// None input
}


int Tetromino::update(const float& tt)
{
	shift_time += shift_clock.restart();
	if (shift_time >= shift_interval)
	{
		(this->*curr_upd_fun)(tt);
		shift_time -= shift_interval;
	}

	if (bGameOver)
		return score;

	return 0;
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
			if (!collision_with_cubes(1,0, &figure))
			{
				figure.move(1,0);
			}
			else
			{
				figure.move(1,0);
				if (!collision_with_cubes(1, 0, &figure))
				{
					figure.move(1, 0);
					return true;
				}

				if (!collision_with_cubes(2, 0, &figure))
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
			if (!collision_with_cubes(-1, 0, &figure))
			{
				figure.move(-1, 0);
			}
			else
			{
				figure.move(-1, 0);
				if (!collision_with_cubes(-1, 0, &figure))
				{
					figure.move(-1, 0);
					return true;
				}

				if (!collision_with_cubes(-2, 0, &figure))
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
			if (!collision_with_cubes(0, -1, &figure))
			{

				figure.move(0, -1);
			}
			else
			{
				figure.move(0, -1);

				if (!collision_with_cubes(0, -1, &figure))
				{
					figure.move(0, -1);
					return true;
				}

				if (!collision_with_cubes(0, -2, &figure))
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


bool Tetromino::collision_with_edges(int dir_x, int dir_y, const Figure* figure)
{

	if (figure->squares[0].getPosition().x + dir_x < LEFT_WALL || figure->squares[0].getPosition().x + dir_x > RIGHT_WALL ||
		figure->squares[0].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure->squares[1].getPosition().x + dir_x < LEFT_WALL || figure->squares[1].getPosition().x + dir_x > RIGHT_WALL ||
			figure->squares[1].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure->squares[2].getPosition().x + dir_x < LEFT_WALL || figure->squares[2].getPosition().x + dir_x > RIGHT_WALL ||
			figure->squares[2].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	else if (figure->squares[3].getPosition().x + dir_x < LEFT_WALL || figure->squares[3].getPosition().x + dir_x > RIGHT_WALL ||
			figure->squares[3].getPosition().y + dir_y > FLOOR_EDGE)
	{
		return true;
	}

	return false;
}

bool Tetromino::collision_with_cubes(int dir_x, int dir_y, const Figure* figure)
{

	sf::Vector2i c1 = figure->indices[0];
	sf::Vector2i c2 = figure->indices[1];
	sf::Vector2i c3 = figure->indices[2];
	sf::Vector2i c4 = figure->indices[3];


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
	if (!collision_with_cubes(1,0, &figure))
	{
		figure.move(1, 0);
		return true;
	}

	if (!collision_with_cubes(2, 0, &figure))
	{
		figure.move(2, 0);
		return true;
	}

	if (!collision_with_cubes(-1,0, &figure))
	{
		figure.move(-1, 0);
		return true;
	}

	if (!collision_with_cubes(-2, 0, &figure))
	{
		figure.move(-2, 0);
		return true;
	}

	if (!collision_with_cubes(0, -1, &figure))
	{
		figure.move(0, -1);
		return true;
	}

	if (!collision_with_cubes(0, -2, &figure))
	{
		figure.move(0, -2);
		return true;
	}
	return false;
}


void Tetromino::update_placeholder()
{
	place_holder.squares[0].setPosition(figure.squares[0].getPosition());
	place_holder.squares[1].setPosition(figure.squares[1].getPosition());
	place_holder.squares[2].setPosition(figure.squares[2].getPosition());
	place_holder.squares[3].setPosition(figure.squares[3].getPosition());
	place_holder.move(0, 0);

	while (!collision_with_cubes(0, 1, &place_holder) && !collision_with_edges(0, 1, &place_holder))
		place_holder.move(0, 1);
	
}

void Tetromino::spawn_figure()
{
	figure.spawnFigure(
		background_tetromino.getPosition().x + ((WIDTH / 2) - 2) * cube_size,
		background_tetromino.getPosition().y - 3 * cube_size,
		nextFigures[0].getTexture(),
		nextFigures[0].type,
		nextFigures[0].rotation
	);


	nextFigures[0] = nextFigures[1];
	nextFigures[0].move(0, -4);
	nextFigures[1] = nextFigures[2];
	nextFigures[1].move(0, -4);
	

	nextFigures[2].spawnFigure(
		background_next.getPosition().x,
		background_next.getPosition().y + cube_size * 9,
		& AM->texture[(rand_gen() % 7) + 8],
		E_FIGURE(rand_gen() % NUMBER_OF_FIGURES),
		rand_gen() % 4);


}