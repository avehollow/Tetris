#pragma once

#include "SYMBOLS.H"

struct GraphicsSettings
{

};

struct MovementSettings
{

};


class OPTIONS
{
public:
	OPTIONS(sf::RenderWindow*, class AM*);
	RESULT manage_input(const sf::Event&);

	void load();
	void save();
	void advance(const float&);
	void display()const;

	virtual ~OPTIONS();


private:
	sf::Text menu[5];
	sf::RenderWindow* const window;
	GraphicsSettings gs;
	MovementSettings ms;

	class AM* const AM_;



	enum MENUTX
	{
		M_BACK = 0,
		M_RESOLUTION,
		M_FULLSCREEN,
		M_TEXTURES,

	};

	class VIDEO
	{
	public:
		VIDEO(sf::RenderWindow*, class AM*);
		void display()const;
		sf::VideoMode* manage_input(const sf::Event&);
	private:
		class AM* const AM_;
		std::vector<sf::VideoMode> video_modes;
		sf::RenderWindow* const window;
	};
	VIDEO video_modes;

};

