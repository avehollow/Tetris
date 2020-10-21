#include "pch.h"
#include "Options.h"
#include "assetmanager.h"
#include "GameWindow.h"
#include "DropDownList.h"

OPTIONS::OPTIONS(GameWindow* w, AM* assetmanager)
{
	//puts("CTOR OPTIONS");

	window = w;
	AM_ = assetmanager;

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


	ddl_vm = window->GUI_.CreateDropDownList(0, 0, 300, 25, 1, "Resolution");
	ddl_vm->setRelativePosition(gui::E_ANCHOR::A_TOP_RIGHT, 310, 25);
	ddl_vm->setFont(AM_->font[AM::E_FONT::F_LARABIEFONTRG]);

	vm = sf::VideoMode::getFullscreenModes();

	for (size_t i = 0; i < vm.size(); i++)
	{
		if (vm[i].bitsPerPixel < 16 ||
			vm[i].width < 800 ||
			vm[i].width == 1768 ||
			vm[i].width == 1366 ||
			vm[i].width == 1176 ||
			vm[i].width == 1152)
		{
			vm.erase(vm.begin() + i);
			i--;
		}
	}

	for (int i = 0, max = vm.size(); i < max; i++)
	{
		ddl_vm->add((std::to_string(vm[i].width) + "x" + std::to_string(vm[i].height) + "x" + std::to_string(vm[i].bitsPerPixel)).c_str(), i);
	}

	show_gui(false);
}


OPTIONS::~OPTIONS()
{
	window->GUI_.erase((void*)b_Applay);
	window->GUI_.erase((void*)b_Back);
	//puts("Destruktor ~OPTIONS");
}

STATE* OPTIONS::handleInput(const sf::Event& event)
{
	STATE* s = this;

	if (b_Back->Pressed() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
	{
		s = nullptr;
	}
	else if (b_Applay->Pressed())
	{
		window->create(vm[ddl_vm->curr_value], "tetris");
	}

	return s;
	
}

int OPTIONS::manageInput(const sf::Event&)
{
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
	ddl_vm->visible(show);
}





