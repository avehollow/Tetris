#pragma once
#include "Figure.h"

enum E_FIGURE
{
	I = 0,
	L,
	T,
	Z,
	O,
	LM,
	ZM
};

class Tetromino : public sf::Drawable
{
public:
	Tetromino(class GameWindow* window, class AM* assetmanager) ;
	~Tetromino() = default;

	void handleInput(const sf::Event& event);
	void ini(int cube_size, int width = 10, int height = 20);
	void onCreate(int size_cube);
	void spawnFigure(float pos_x, float pos_y, sf::Texture* texture, E_FIGURE type);
private:
	sf::RectangleShape tetromino[200];
	Figure figure;
	int collisions[200] = { 0 };

	sf::RectangleShape background_tetromino;

	class GameWindow* window;
	// AVE LOOK usun�� potem
	class AM* am;

	int LEFT_WALL;
	int RIGHT_WALL;
	int FLOOR_EDGE;

	int WIDTH;
	int HEIGHT;

	// Inherited via Drawable
	inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

inline void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background_tetromino);
	for (size_t y = 0; y < 20; y++)
		for (size_t x = 0; x < 10; x++)
			target.draw(tetromino[(10 * y) + x]);

	target.draw(figure);
}