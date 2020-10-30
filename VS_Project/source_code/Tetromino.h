#pragma once
#include "Figure.h"
#include "WORLD.h"


class Tetromino: public WORLD
{
public:
	Tetromino();
	~Tetromino() = default;

	void handleInput(const sf::Event& event);
	void ini(int width = 10, int height = 20);
	void draw(GameWindow* __restrict const window) const ;
	void update(const float& tt);
	void pause();
	void onCreate();

private:
	bool wall_kick();
	bool collision_with_edges(float dir_x, float dir_y);
	bool collision_with_cubes(float dir_x, float dir_y);

private:
	Figure figure;
	sf::RectangleShape tetromino[200];
	int collisions[200];
	sf::RectangleShape background_tetromino;

	std::mt19937 rand_gen;

	sf::Clock shift_clock;
	sf::Time  shift_interval;
	sf::Time  shift_time;

	int LEFT_WALL;
	int RIGHT_WALL;
	int FLOOR_EDGE;

	int WIDTH;
	int HEIGHT;

#define CUBE_DIMENSIONS 50.0F
	float cube_size_percent;
	int cube_size;


};

inline void Tetromino::draw(GameWindow* __restrict const window) const
{
	window->draw(background_tetromino);
	for (size_t y = 0; y < HEIGHT; y++)
		for (size_t x = 0; x < WIDTH; x++)
			window->draw(tetromino[(WIDTH * y) + x]);

	figure.draw(window);
}

inline void Tetromino::pause()
{
	shift_clock.restart();
	shift_time = sf::seconds(0);
}