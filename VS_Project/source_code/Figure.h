#pragma once

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

class Figure: public sf::Drawable
{
	friend class Tetromino;
public:
	Figure();
	~Figure() = default;

	void move(int dirx, int diry);
	void ini(float cube_size, class AM_* assetmanager, const sf::Vector2f& tetromino_pos);
	void onCreate(int size_cube, const sf::Vector2f& tetromino_pos);
	void rotate();
	void spawnFigure(float pos_x, float pos_y, sf::Texture* texture, E_FIGURE type);

private:
	void be_Z_(float pos_x, float pos_y, sf::Texture* texture);
	void be_L_(float pos_x, float pos_y, sf::Texture* texture);
	void be_I_(float pos_x, float pos_y, sf::Texture* texture);
	void be_T_(float pos_x, float pos_y, sf::Texture* texture);
	void be_ZM_(float pos_x, float pos_y, sf::Texture* texture);
	void be_LM_(float pos_x, float pos_y, sf::Texture* texture);
	void be_O_(float pos_x, float pos_y, sf::Texture* texture);

private:
	std::array<sf::RectangleShape, 4> squares;
	sf::RectangleShape center_sprite;

	std::array<sf::Vector2i, 4> indices;
	sf::Vector2f center_pos;
	sf::Vector2f tetromino_pos;
	float cube_size;
	bool isI;

	// Inherited via Drawable
	inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

inline void Figure::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& sq : squares)
		target.draw(sq);

	target.draw(center_sprite);
}

