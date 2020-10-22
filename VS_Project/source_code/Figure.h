#pragma once

class Figure
{
	friend class GAME;
public:
	Figure();
	~Figure() = default;

	void draw(class GameWindow*)const; 
	void move(float dirx, float diry);
	void setCubeSize(float size);


	void be_Z_(float pos_x, float pos_y, sf::Texture* texture);
	void be_L_(float pos_x, float pos_y, sf::Texture* texture);
	void be_I_(float pos_x, float pos_y, sf::Texture* texture);
	void be_T_(float pos_x, float pos_y, sf::Texture* texture);
	void be_ZM_(float pos_x, float pos_y, sf::Texture* texture);
	void be_LM_(float pos_x, float pos_y, sf::Texture* texture);

private:
	std::array<sf::RectangleShape, 4> squares;

	sf::RectangleShape center_sprite;
	sf::Vector2f center_pos;
	float CUBE_SIZE;
};

