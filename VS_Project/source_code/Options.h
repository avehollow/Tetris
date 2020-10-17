#pragma once

#include "SYMBOLS.H"

namespace gui
{
	class Button;
	class DropDownList;
}

struct GraphicsSettings
{

};

struct MovementSettings
{

};


class OPTIONS
{
public:
	OPTIONS(class GameWindow* w, class AM*);
	RESULT manage_input(const sf::Event&);

	void load();
	void save();
	void advance(const float&);
	void display()const;

	virtual ~OPTIONS();

private:
	sf::Text menu[5];
	GraphicsSettings gs;
	MovementSettings ms;

	class AM* const AM_;
	class GameWindow* const window;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;

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

