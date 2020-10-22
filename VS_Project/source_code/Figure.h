#pragma once

class Figure
{
	friend class GAME;
public:
	Figure(class GameWindow* window);
	~Figure() = default;

	void draw()const; 
	void move(int dirx, int diry);
	void ini(class Tetromino* tetromino);
	void setCubeSize(int size);
	void onCreate(int size_cube);

	void be_Z_(float pos_x, float pos_y, sf::Texture* texture);
	void be_L_(float pos_x, float pos_y, sf::Texture* texture);
	void be_I_(float pos_x, float pos_y, sf::Texture* texture);
	void be_T_(float pos_x, float pos_y, sf::Texture* texture);
	void be_ZM_(float pos_x, float pos_y, sf::Texture* texture);
	void be_LM_(float pos_x, float pos_y, sf::Texture* texture);

private:
	std::array<sf::RectangleShape, 4> squares;
	sf::RectangleShape center_sprite;

	std::array<sf::Vector2i, 4> pp;
	sf::Vector2f center_pos;
	int CUBE_SIZE;

	class Tetromino* tetromino;
	class GameWindow* window;

	bool isI;
};

