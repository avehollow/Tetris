#include "pch.h"
#include "Options.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "DropDownList.h"

OPTIONS::OPTIONS(GameWindow* w, AM* assetmanager)
    : window(w)
	, AM_(assetmanager)
{
	//puts("CTOR OPTIONS");

	b_Back = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 250, 106);
	b_Back->setTexture(AM_->texture[AM::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));
	b_Back->visible(false);


	b_Applay = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Applay->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 510, 106);
	b_Applay->setTexture(AM_->texture[AM::E_TEXTURE::T_BAPPLAY]);
	b_Applay->setHoveOverColor(sf::Color::White);
	b_Applay->setFillColor(sf::Color(180, 180, 180));
	b_Applay->visible(false);

}


OPTIONS::~OPTIONS()
{
	window->GUI_.erase((void*)b_Applay);
	window->GUI_.erase((void*)b_Back);
	//puts("Destruktor ~OPTIONS");
}

STATE* OPTIONS::handleInput(const sf::Event&)
{
	return nullptr;
}

int OPTIONS::manageInput(const sf::Event&)
{
	if (b_Back->Pressed())
		return RESULT::B_BACK;

	return 0;
}

void OPTIONS::update(const float&)
{

}

void OPTIONS::render() const
{
}



void OPTIONS::show() 
{
	show_gui(true);
}

void OPTIONS::hide() 
{
	show_gui(false);
}

void OPTIONS::show_gui(bool show)
{
	b_Back->visible(show);
	b_Applay->visible(show);
}




