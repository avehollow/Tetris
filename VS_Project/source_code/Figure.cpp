#include "pch.h"
#include "Figure.h"
#include "GameWindow.h"
#include "Tetromino.h"

Figure::Figure(GameWindow* w)
	: window(w)
{
	CUBE_SIZE = 0.0f;
	center_sprite.setSize(sf::Vector2f(5, 5));
	center_sprite.setFillColor(sf::Color::Green);

	
}

void Figure::draw()const
{
	for (auto& sq : squares)
		window->draw(sq);

	window->draw(center_sprite);
}

void Figure::move(int dirx, int diry)
{
	for (int i = 0; i < 4; i++)
	{
		squares[i].move(dirx, diry);
		pp[i].x = (squares[i].getPosition().x - tetromino->getPosition().x ) / CUBE_SIZE;
		pp[i].y = (squares[i].getPosition().y - tetromino->getPosition().y ) / CUBE_SIZE;
	}
	std::cout << "X: " << pp[0].x << "  Y: " << pp[0].y << "\n";
	center_pos.x += dirx;
	center_pos.y += diry;
	center_sprite.setPosition(center_pos);

}

void Figure::ini(Tetromino* tetromino)
{
	this->tetromino = tetromino;
}

void Figure::setCubeSize(int size)
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
	move(0, 0);
	isI = false;
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
	move(0, 0);
	isI = false;
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
	move(0, 0);
	isI = true;
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
	move(0, 0);
	isI = false;
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
	move(0, 0);
	isI = false;
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
	move(0, 0);
	isI = false;
}

void Figure::be_O_(float pos_x, float pos_y, sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x +CUBE_SIZE, pos_y);
	squares[2].setPosition(pos_x, pos_y + CUBE_SIZE);
	squares[3].setPosition(pos_x +CUBE_SIZE, pos_y + CUBE_SIZE);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
	move(0, 0);
	isI = false;
}

void Figure::onCreate(int size_cube)
{
	CUBE_SIZE = size_cube;
	for (int i = 0; i < 4; i++)
	{
		squares[i].setPosition(tetromino->getPosition().x + size_cube * pp[i].x, tetromino->getPosition().y + size_cube * pp[i].y);
		squares[i].setSize(sf::Vector2f(size_cube, size_cube));
	}
	if (isI)
		center_pos = sf::Vector2f(squares[2].getPosition().x - (size_cube / 2.0f), squares[2].getPosition().y - (size_cube / 2.0f));
	else
		center_pos = squares[1].getPosition();

	center_sprite.setPosition(center_pos);
}
