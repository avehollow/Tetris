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

	void ini(float cube_size, const sf::Vector2f& tetromino_pos);
	void spawnFigure(float posX, float posY, const sf::Texture* texture, E_FIGURE type, size_t rotation);
	void draw(GameWindow* __restrict const window);
	
	void move(int dirx, int diry);
	void rotate();

	void setPosition(const Figure& figure);
	void onCreate(int size_cube, const sf::Vector2f& tetromino_pos);
	
	void setTexture(const sf::Texture* texture);
	const sf::Texture* getTexture() const;

	void setGlowTexture(const sf::Texture* texture);
	
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
	E_FIGURE type;
	short rotation;


	sf::RectangleShape glowSpr;
};

inline void Figure::draw(GameWindow* __restrict const window) 
{
	glowSpr.setFillColor(squares[0].getTexture()->copyToImage().getPixel(squares[0].getSize().x / 2.0f, squares[0].getSize().x / 2.0f));
	glowSpr.setSize(sf::Vector2f(squares[0].getSize().x + (25.f * window->getSize().x / 1920.0f), squares[0].getSize().y + (25.f * window->getSize().y / 1080.0f)));
	for (auto& sq : squares)
	{
		glowSpr.setPosition(sq.getPosition().x - (12.5f * (window->getSize().x / 1920.0f)), sq.getPosition().y - (12.5f * (window->getSize().y / 1080.0f)));
		window->draw(sq);
		window->draw(glowSpr, sf::BlendAdd);
	}

	//window->draw(center_sprite);
}

inline void Figure::setTexture(const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);
}

inline void Figure::setGlowTexture(const sf::Texture* texture)
{
	glowSpr.setTexture(texture);
}

inline const sf::Texture* Figure::getTexture() const
{
	return squares[0].getTexture();
}
