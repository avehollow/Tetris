#include "pch.h"
#include "GameWindow.h"

GameWindow::GameWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings )
	: sf::RenderWindow(mode, title, style, settings)
	, GUI_(this)
{

}

GameWindow::~GameWindow()
{
}

void GameWindow::onCreate()
{
	GUI_.onRecreateWindow();
}
