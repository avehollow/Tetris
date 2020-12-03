#include "pch.h"
#include "Figure.h"


Figure::Figure()
{
	center_sprite.setSize(sf::Vector2f(5, 5));
	center_sprite.setFillColor(sf::Color(255,0,0));
	rotation = 0;

	for (auto& idx : indices)
	{
		idx.x = 0;
		idx.y = 0;
	}
}



void Figure::move(int dirx, int diry)
{
	for (int i = 0; i < 4; i++)
	{
		squares[i].move(dirx * cube_size, diry * cube_size);
		indices[i].x = (squares[i].getPosition().x - tetromino_pos.x ) / cube_size;
		indices[i].y = (squares[i].getPosition().y - tetromino_pos.y ) / cube_size;
	}

	center_pos.x += cube_size * dirx;
	center_pos.y += cube_size * diry;
	center_sprite.setPosition(center_pos);

}

void Figure::ini(float cube_size, const sf::Vector2f& tetromino_pos)
{
	this->cube_size = cube_size;
	this->tetromino_pos = tetromino_pos;

	for (auto& sq : squares)
		sq.setSize(sf::Vector2f(cube_size, cube_size));
}




void Figure::be_Z_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);
	
	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x + cube_size, pos_y);
	squares[2].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[3].setPosition(pos_x + 2*cube_size, pos_y + cube_size);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
	
	type = E_FIGURE::Z;
}

void Figure::be_L_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y);
	squares[1].setPosition(pos_x + cube_size, pos_y);
	squares[2].setPosition(pos_x + 2*cube_size, pos_y);
	squares[3].setPosition(pos_x + 2*cube_size, pos_y + cube_size);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
	
	type = E_FIGURE::L;
}

void Figure::be_I_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + cube_size);
	squares[1].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[2].setPosition(pos_x + 2*cube_size, pos_y + cube_size);
	squares[3].setPosition(pos_x + 3*cube_size, pos_y + cube_size);

	center_pos = sf::Vector2f(squares[2].getPosition().x - (cube_size / 2), squares[2].getPosition().y - (cube_size / 2));
	center_sprite.setPosition(center_pos);
	move(0, 0);
	type = E_FIGURE::I;
}

void Figure::be_T_(float pos_x, float pos_y,const sf::Texture* texture)
{

	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + cube_size);
	squares[1].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[2].setPosition(pos_x + cube_size, pos_y);
	squares[3].setPosition(pos_x + 2*cube_size, pos_y + cube_size);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);

	type = E_FIGURE::T;
}

void Figure::be_ZM_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + cube_size);
	squares[1].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[2].setPosition(pos_x + cube_size, pos_y);
	squares[3].setPosition(pos_x + 2*cube_size, pos_y);


	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);

	type = E_FIGURE::ZM;
}

void Figure::be_LM_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x, pos_y + cube_size);
	squares[1].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[2].setPosition(pos_x + 2*cube_size, pos_y + cube_size);
	squares[3].setPosition(pos_x + 2*cube_size, pos_y);

	center_pos = squares[1].getPosition();
	center_sprite.setPosition(center_pos);
	
	type = E_FIGURE::LM;
}

void Figure::be_O_(float pos_x, float pos_y,const sf::Texture* texture)
{
	for (auto& sq : squares)
		sq.setTexture(texture);

	squares[0].setPosition(pos_x + cube_size, pos_y);
	squares[1].setPosition(pos_x + cube_size +cube_size, pos_y);
	squares[3].setPosition(pos_x + cube_size, pos_y + cube_size);
	squares[2].setPosition(pos_x + cube_size +cube_size, pos_y + cube_size);

	center_pos = sf::Vector2f(squares[2].getPosition().x - (cube_size / 2), squares[2].getPosition().y - (cube_size / 2));
	center_sprite.setPosition(center_pos);
	
	type = E_FIGURE::O;
}


void Figure::setPosition(const Figure& figure)
{
	for (size_t i = 0; i < 4; i++)
		squares[i].setPosition(figure.squares[i].getPosition());

	move(0, 0);
}

void Figure::onCreate(int size_cube, const sf::Vector2f& tetromino_pos)
{
	cube_size = size_cube;
	for (int i = 0; i < 4; i++)
	{
		squares[i].setPosition(tetromino_pos.x + size_cube * indices[i].x, tetromino_pos.y + size_cube * indices[i].y);
		squares[i].setSize(sf::Vector2f(size_cube, size_cube));
	}

	if (type == E_FIGURE::I || type == E_FIGURE::O)
		center_pos = sf::Vector2f(squares[2].getPosition().x - (size_cube / 2.0), squares[2].getPosition().y - (size_cube / 2.0));
	else
		center_pos = squares[1].getPosition();

	center_sprite.setPosition(center_pos);

	this->tetromino_pos.x = tetromino_pos.x; 
	this->tetromino_pos.y = tetromino_pos.y;
	move(0, 0);
}

void Figure::rotate()
{
	
	sf::Vector2f Vr = squares[0].getPosition() - center_pos;
	sf::Vector2f Vt = sf::Vector2f((Vr.x * 0) + (Vr.y * -1), (Vr.x * 1) + (Vr.y * 0));


	//		 |-			  -|		|-	   -|
	//		 | 0		-1 |		|	Vx	|
	//		 |			   |	*  	|		|
	//		 | 1		 0 |		|	Vy	|
	//		 |-			  -|		|-	   -|

	sf::Vector2f TransformVector = sf::Vector2f(center_pos + Vt);
	squares[0].setPosition(TransformVector);


	Vr = squares[1].getPosition() - center_pos;
	Vt = sf::Vector2f((Vr.x * 0) + (Vr.y * -1), (Vr.x * 1) + (Vr.y * 0));

	// AVE LOOK mozna usprawnic
	TransformVector = sf::Vector2f(center_pos + Vt);
	squares[1].setPosition(TransformVector);



	Vr = squares[2].getPosition() - center_pos;
	Vt = sf::Vector2f((Vr.x * 0) + (Vr.y * -1), (Vr.x * 1) + (Vr.y * 0));

	TransformVector = sf::Vector2f(center_pos + Vt);
	squares[2].setPosition(TransformVector);



	Vr = squares[3].getPosition() - center_pos;
	Vt = sf::Vector2f((Vr.x * 0) + (Vr.y * -1), (Vr.x * 1) + (Vr.y * 0));

	TransformVector = sf::Vector2f(center_pos + Vt);
	squares[3].setPosition(TransformVector);

	move(0, 0);
}

void Figure::spawnFigure(float posX, float posY, const sf::Texture* texture, E_FIGURE type, size_t rotation)
{

	float xx = posX;
	float yy = posY;
	switch (type)
	{
	case I:
		this->be_I_(xx, yy, texture);
		break;
	case L:
		this->be_L_(xx, yy, texture);
		break;
	case T:
		this->be_T_(xx, yy, texture);
		break;
	case Z:
		this->be_Z_(xx, yy, texture);
		break;
	case O:
		this->be_O_(xx, yy, texture);
		break;
	case LM:
		this->be_LM_(xx, yy, texture);
		break;
	case ZM:
		this->be_ZM_(xx, yy, texture);
		break;
	default:
		break;
	}
	for (size_t i = 0; i < rotation; i++)
		rotate();
	
	this->rotation = rotation;
	this->move(0, 0);
}
