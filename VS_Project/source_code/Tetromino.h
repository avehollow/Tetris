#pragma once
#include "assetmanager.h"
class Tetromino
{
	friend class GAME;
public:
	Tetromino(class GameWindow*);
	~Tetromino();

	void draw()const;
	void ini(int SIZE_CUBE);
	void onCreate(int size_cube);
	sf::Vector2f getPosition() const { return background_tetromino.getPosition(); }
private:
	sf::RectangleShape tetromino[200];
	int collisions[200] = { 0 };

	sf::RectangleShape background_tetromino;

	class GameWindow* window;
	AM am_;

	int LEFT_WALL;
	int RIGHT_WALL;
	int FLOOR_EDGE;

	
};

