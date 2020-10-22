#pragma once
#include "GUI.h"

class GameWindow final: public sf::RenderWindow
{
public:
	GameWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	virtual ~GameWindow();

	gui::GUI GUI_;

	void addOnCreate(class STATE* state)
	{
		on_create.push_back(state);
	};
protected:
	virtual void onCreate();
	std::vector<class STATE*> on_create;
};

