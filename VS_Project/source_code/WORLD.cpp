#include "pch.h"
#include "WORLD.h"



GameWindow* WORLD::window = nullptr;
AM_* WORLD::AM = nullptr;

void WORLD::ini()
{
	// AVE LOOK after reimplementing the GUI:
	// read settings file with resolution(save resolution as width, height, bpp separately)
	// -create appropriate sf::Videomode
	//- compare created sf::Videomode with proper avible video modes and if some valid video mode is equal then create window
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
