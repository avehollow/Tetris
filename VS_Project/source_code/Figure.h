#pragma once
#include "GameWindow.h"

#define NUMBER_OF_FIGURES 7
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

class Figure
{
	friend class Tetromino;
public:
	Figure();
	~Figure() = default;

	void move(int dirx, int diry);
	void ini(float cube_size, const sf::Vector2f& tetromino_pos);
	void onCreate(int size_cube, const sf::Vector2f& tetromino_pos);
	void rotate();
	void spawnFigure(float posX, float posY, const sf::Texture* texture, E_FIGURE type, size_t rotation);
	void draw(GameWindow* __restrict const window) const;
	void setTexture(const sf::Texture* texture);
	const sf::Texture* getTexture() const;
	
private:
	void be_Z_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_L_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_I_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_T_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_ZM_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_LM_(float pos_x, float pos_y, const sf::Texture* texture);
	void be_O_(float pos_x, float pos_y,  const sf::Texture* texture);

private:
	std::array<sf::RectangleShape, 4> squares;
	sf::RectangleShape center_sprite;

	std::array<sf::Vector2i, 4> indices;
	sf::Vector2f center_pos;
	sf::Vector2f tetromino_pos;
	float cube_size;
	// AVE LOOK zamieniæ na bool?
	E_FIGURE type;
	short rotation;

};

inline void Figure::draw(GameWindow* __restrict const window) const
{
	for (auto& sq : squares)
		window->draw(sq);

	window->draw(center_sprite);
}

inline void Figure::setTexture(const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);
}

inline const sf::Texture* Figure::getTexture() const
{
	return squares[0].getTexture();
}
