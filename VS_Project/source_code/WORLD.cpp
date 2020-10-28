#include "pch.h"
#include "WORLD.h"
#include "assetmanager.h"
#include "GameWindow.h"


GameWindow* WORLD::window = nullptr;
AM_* WORLD::AM = nullptr;

void WORLD::ini()
{
	window = new GameWindow(sf::VideoMode::getDesktopMode(), "Tetris", sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar);
	AM = new AM_();;
}

void WORLD::free()
{
	delete window;
	delete AM;
}
