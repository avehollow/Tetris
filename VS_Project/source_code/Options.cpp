#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Options.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "DropDownList.h"

OPTIONS::OPTIONS(GameWindow* w, AM* assetmanager)
    : window(w)
	, video_modes(w, assetmanager)
	, AM_(assetmanager)
{
	//puts("CTOR OPTIONS");
	
}

RESULT OPTIONS::manage_input(const sf::Event& event)
{
	RESULT rs = RESULT::R_NONE;
	if (b_Back->Pressed())
	{
		rs = RESULT::R_EXIT;
	}

	return rs;
}





void OPTIONS::load()
{

	b_Back = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 250, 106);
	b_Back->setTexture(AM_->texture[AM::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));

	

	b_Applay = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Applay->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 510, 106);
	b_Applay->setTexture(AM_->texture[AM::E_TEXTURE::T_BAPPLAY]);
	b_Applay->setHoveOverColor(sf::Color::White);
	b_Applay->setFillColor(sf::Color(180, 180, 180));
}

void OPTIONS::save()
{
	window->GUI_.erase((void*)b_Back);
	window->GUI_.erase((void*)b_Applay);
}

void OPTIONS::advance(const float& d)
{


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
