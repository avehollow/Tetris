#include "pch.h"
#include "Figure.h"
#include "GameWindow.h"


Figure::Figure()
{
	center_sprite.setSize(sf::Vector2f(5, 5));
	center_sprite.setFillColor(sf::Color::Green);

}

void Figure::draw(GameWindow* window)const
{
	for (auto& sq : squares)
		window->draw(sq);

	window->draw(center_sprite);
}

void Figure::move(float dirx, float diry)
{
	for (auto& sq : squares)
		sq.move(dirx, diry);

	center_pos.x += dirx;
	center_pos.y += diry;
	center_sprite.setPosition(center_pos);

}

void Figure::setCubeSize(float size)
{
	CUBE_SIZE = size;
	for (auto& sq : squares)
	{
		sq.setSize(sf::Vector2f(CUBE_SIZE, CUBE_SIZE));
	}
}

void Figure::be_Z_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);
	

	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x + CUBE_SIZE, pos_y);
	squares[2].setPosition(pos_x + CUBE_SIZE, pos_y + CUBE_SIZE);
	squares[3].setPosition(pos_x + 2*CUBE_SIZE, pos_y + CUBE_SIZE);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
}

void Figure::be_L_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x + CUBE_SIZE, pos_y);
	squares[2].setPosition(pos_x + 2*CUBE_SIZE, pos_y);
	squares[3].setPosition(pos_x + 2*CUBE_SIZE, pos_y + CUBE_SIZE);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
}

void Figure::be_I_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x + CUBE_SIZE, pos_y);
	squares[2].setPosition(pos_x + 2*CUBE_SIZE, pos_y);
	squares[3].setPosition(pos_x + 3*CUBE_SIZE, pos_y);

	center_pos = sf::Vector2f(squares[2].getPosition().x - (CUBE_SIZE / 2), squares[2].getPosition().y - (CUBE_SIZE / 2));
	center_sprite.setPosition(center_pos);
}

void Figure::be_T_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + CUBE_SIZE);
	squares[1].setPosition(pos_y + CUBE_SIZE, pos_y + CUBE_SIZE);
	squares[2].setPosition(pos_y + CUBE_SIZE, pos_y);
	squares[3].setPosition(pos_y + 2*CUBE_SIZE, pos_y + CUBE_SIZE);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
}

void Figure::be_ZM_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + CUBE_SIZE);
	squares[1].setPosition(pos_x + CUBE_SIZE, pos_y + CUBE_SIZE);
	squares[2].setPosition(pos_x + CUBE_SIZE, pos_y);
	squares[3].setPosition(pos_x + 2*CUBE_SIZE, pos_y);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
}

void Figure::be_LM_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + CUBE_SIZE);
	squares[1].setPosition(pos_x + CUBE_SIZE, pos_y + CUBE_SIZE);
	squares[2].setPosition(pos_x + 2*CUBE_SIZE, pos_y + CUBE_SIZE);
	squares[3].setPosition(pos_x + 2*CUBE_SIZE, pos_y);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
}
