#pragma once
#include "assetmanager.h"
class Tetromino
{
	friend class GAME;
public:
	Tetromino(class GameWindow*);
	~Tetromino();

	void draw()const;
	void ini(float SIZE_CUBE);
	void onCreate(float size_cube);
	sf::Vector2f getPosition() const { return background_tetromino.getPosition(); }
private:
	sf::RectangleShape tetromino[200];
	int collisions[200] = { 0 };

	sf::RectangleShape background_tetromino;

	class GameWindow* window;
	AM am_;

	float LEFT_WALL;
	float RIGHT_WALL;
	float FLOOR_EDGE;
};

