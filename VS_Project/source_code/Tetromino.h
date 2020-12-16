#pragma once
#include "Figure.h"
#include "WORLD.h"
#include "Flipbook/ScreenFlipbookManager.h"
#include "Settings.h"

class Tetromino: public WORLD
{
public:
	Tetromino() = default;
	~Tetromino() = default;

	void startUp();
	void handleInput(const sf::Event& event);
	void ini(int width = 10, int height = 20);
	void draw(GameWindow* __restrict const window) const ;
	int update(const float& tt);
	void pause();
	void onCreate();
	void setMovement(const Settings::Movement* ms);
private:
	void play_anim_tetris(const float& tt);
	void shift_tetris(const float& tt);
	void tick(const float& tt);

	void place_figure();

	void standard_input(const sf::Event& event);
	void disable_input(const sf::Event& event);

	void update_placeholder();
	void spawn_figure();
	void update_score(size_t pointsToAdd);
	void check_tetris();
	bool wall_kick();
	bool collision_with_edges(int dir_x, int dir_y, const Figure* figure);
	bool collision_with_cubes(int dir_x, int dir_y, const Figure* figure);

	void play_anim_fire();
	void load_anim();
private:
	ScreenFlipbookManager SAM;

	Figure figure;
	Figure place_holder;

	std::array<Figure, 3> nextFigures;
	
	sf::RectangleShape tetromino[200];
	int collisions[240];


	sf::RectangleShape background_tetromino;
	sf::RectangleShape background_score;
	sf::RectangleShape background_next;
	sf::Text txScore;
	sf::Text txNext;
	sf::Text txNumScore;

	std::random_device rd;
	std::mt19937 rand_gen;

	std::vector<int> tetris_row;

	Settings::Movement movement;

	std::size_t score;
	int LEFT_WALL;
	int RIGHT_WALL;
	int FLOOR_EDGE;
	int CEIL_EDGE;

	int WIDTH;
	int HEIGHT;

#define CUBE_DIMENSIONS 50.0F
	float cube_size_percent;
	int cube_size;

	bool bGameOver;
	bool elo();

	void (Tetromino::*curr_upd_fun)(const float& tt);
	void (Tetromino::*curr_hdl_fun)(const sf::Event& event);

	int numTetris;
	float shift_time;
	float shift_interval;
	int which_anim;

	bool bFireFlipbook;
};



inline void Tetromino::draw(GameWindow* __restrict const window) const
{
	window->draw(background_tetromino);
	for (size_t y = 0; y < HEIGHT; y++)
		for (size_t x = 0; x < WIDTH; x++)
			window->draw(tetromino[(WIDTH * y) + x]);


	place_holder.draw(window);
	figure.draw(window);

	window->draw(background_score);
	window->draw(background_next);
	window->draw(txScore);
	window->draw(txNumScore);
	window->draw(txNext);
	
	for (auto& f : nextFigures)
		f.draw(window);

	SAM.render();
}

inline void Tetromino::pause()
{
	shift_time = 0;
	SAM.update(false);
}