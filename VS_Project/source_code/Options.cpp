#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Options.h"
#include "assetmanager.h"

OPTIONS::OPTIONS(sf::RenderWindow* w, AM* assetmanager)
    : window(w)
	, video_modes(w, assetmanager)
	, AM_(assetmanager)
{
	//puts("CTOR OPTIONS");
	///
	// MENU
	/// 
	const size_t SIZE = sizeof(menu) / sizeof(sf::Text);
	for (size_t i = 0; i < SIZE; i++)
	{
		menu[i].setFont(AM_->font[AM::E_FONT::F_LARABIEFONTRG]);
		menu[i].setString("--");
		menu[i].setFillColor(sf::Color::Magenta);
		menu[i].setCharacterSize(25);
		menu[i].setStyle(sf::Text::Style::Italic);
		menu[i].setPosition(w->getSize().x * 0.05, w->getSize().y * (0.05 + (0.05 * i)));
	}
	menu[MENUTX::M_BACK].setString("BACK");
	menu[MENUTX::M_BACK].setPosition(w->getSize().x * 0.85, w->getSize().y * (0.05));

	menu[MENUTX::M_RESOLUTION].setString("Resolution");
	menu[MENUTX::M_FULLSCREEN].setString("Fullscreen");
	menu[MENUTX::M_TEXTURES].setString("Textures");



}

RESULT OPTIONS::manage_input(const sf::Event& event)
{
	RESULT rs = RESULT::R_NONE;
	if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left
		&& menu[MENUTX::M_BACK].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
	{
		rs = RESULT::R_EXIT;
	}

	return rs;
}



void OPTIONS::load()
{
}

void OPTIONS::save()
{
}

void OPTIONS::advance(const float& d)
{
	for (auto& tx : menu)
	{
		if (tx.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
			tx.setFillColor(sf::Color::Green);
		else
			tx.setFillColor(sf::Color::Magenta);
	}

}

void OPTIONS::display() const
{
	for (const auto& tx : menu)
		window->draw(tx);
	video_modes.display();
}

OPTIONS::~OPTIONS()
{
	//puts("Destruktor ~OPTIONS");
}




OPTIONS::VIDEO::VIDEO(sf::RenderWindow* w, class AM* assetmanager)
	: video_modes(sf::VideoMode::getFullscreenModes())
	, window(w)
	, AM_(assetmanager)
{


	for (size_t i = 0; i < video_modes.size(); i++)
	{
		if (video_modes[i].bitsPerPixel != 32 || 
			video_modes[i].width < 800 ||
			video_modes[i].width == 1768 ||
			video_modes[i].width == 1366 ||
			video_modes[i].width == 1176 ||
			video_modes[i].width == 1152)
		{
			video_modes.erase(video_modes.begin() + i);
			i--;
		}
	}

}


void OPTIONS::VIDEO::display()const
{
	sf::Text text;
	size_t SIZE = video_modes.size();
	text.setFont(AM_->font[AM::E_FONT::F_LARABIEFONTRG]);
	text.setCharacterSize(15);

	//TODO !@!
	char temp[255] = {'\0'};

	for (size_t i = 0; i < SIZE; i++)
	{
		text.setPosition(window->getSize().x * 0.15, window->getSize().y * (0.05 + (0.05 * i)));
		//text.setString(std::to_string(video_modes[i].width) + "-" + std::to_string(video_modes[i].height) + "x" +std::to_string(video_modes[i].bitsPerPixel));
		sprintf(temp,"%u - %u x %u", video_modes[i].width, video_modes[i].height, video_modes[i].bitsPerPixel);
		text.setString(temp);
		window->draw(text);
	}
}

sf::VideoMode* OPTIONS::VIDEO::manage_input(const sf::Event&)
{
	// TODO: insert return statement here
	return nullptr;
}
