#include "pch.h"
#include "WORLD.h"



GameWindow* WORLD::window = nullptr;
AM_* WORLD::AM = nullptr;

void WORLD::ini()
{
#ifdef FS
	window = new GameWindow(sf::VideoMode::getDesktopMode(), "Tetris", sf::Style::Fullscreen | sf::Style::Close | sf::Style::Titlebar);
#else
	window = new GameWindow(sf::VideoMode(1280,720), "Tetris", sf::Style::Close | sf::Style::Titlebar);
#endif
	AM = new AM_();;
}

void WORLD::free()
{
	delete window;
	delete AM;
}
