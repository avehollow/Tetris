#include "pch.h"
#include "Options.h"
#include "DropDownList.h"


OPTIONS options;

OPTIONS::OPTIONS()
{
	//puts("CTOR OPTIONS");
}


OPTIONS::~OPTIONS()
{
	//puts("Destruktor ~OPTIONS");
}

ISTATE* OPTIONS::handleInput(const sf::Event& event)
{
	ISTATE* state = this;

	if (b_Back->Pressed() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
	{
		state = nullptr;
	}
	else if (b_Applay->Pressed())
	{
#ifdef FS
		window->create(vm[ddl_vm->curr_value], "Tetris", sf::Style::Fullscreen);
#else
		window->create(vm[ddl_vm->curr_value], "Tetris");
#endif // FS

	}

	return state;
	
}


void OPTIONS::update(const float& d)
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

void OPTIONS::onCreate()
{
}

void OPTIONS::startUp()
{

	b_Back = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 250, 106);
	b_Back->setTexture(AM->texture[AM_::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));


	b_Applay = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Applay->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_RIGHT, 510, 106);
	b_Applay->setTexture(AM->texture[AM_::E_TEXTURE::T_BAPPLAY]);
	b_Applay->setHoveOverColor(sf::Color::White);
	b_Applay->setFillColor(sf::Color(180, 180, 180));


	ddl_vm = window->GUI_.CreateDropDownList(0, 0, 300, 25, 1, "Resolution");
	ddl_vm->setRelativePosition(gui::E_ANCHOR::A_CENTER_TOP, -150, 25);
	ddl_vm->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	ddl_vm->setOutlineColor(sf::Color(50, 50, 50));

	vm = sf::VideoMode::getFullscreenModes();

	for (size_t i = 0; i < vm.size(); i++)
	{
		if (vm[i].bitsPerPixel != 32 ||
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


void OPTIONS::show_gui(bool show)
{
	b_Back->visible(show);
	b_Applay->visible(show);
	ddl_vm->visible(show);
}





