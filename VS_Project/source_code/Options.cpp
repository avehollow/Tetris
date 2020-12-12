#include "pch.h"
#include "Options.h"
#include "DropDownList.h"
#include "SliderList.h"
#include "Resource.h"

#define xx(p) ((p) * ppX)
#define yy(p) ((p) * ppY)

OPTIONS options;

OPTIONS::OPTIONS()
{
	
}


OPTIONS::~OPTIONS()
{

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

		
		HCURSOR hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_CURSOR));
		if (hCursor != NULL)
		{
			SetClassLong(
				window->getSystemHandle(),							
				GCL_HCURSOR,									   
				(LONG)hCursor										
			);
		}
		
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_ICON));
		if (hIcon != NULL)
		{
			SetClassLong(
				window->getSystemHandle(),						
				GCL_HICON,										
				(LONG)hIcon										
			);
		}

	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i vi = window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
		for (size_t i = 0, max = sizeof control_keys / sizeof(sf::Text); i < max; i++)
		{
			if (control_keys[i].getGlobalBounds().contains(sf::Vector2f(vi)))
			{
				ctx->setFillColor(sf::Color::White);
				ctx = &control_keys[i];
				ctx->setFillColor(sf::Color::Magenta);
				break;
			}
		}

		for (const auto& i : k)
		{
			if(i.rec.getGlobalBounds().contains(sf::Vector2f(vi)))
			{

			}
		}
	}

	return state;
}


void OPTIONS::update(const float& d)
{

}

void OPTIONS::render() const
{
	window->draw(keyboard);
	for (auto& i : k)
		window->draw(i.rec);
	
	for (size_t i = 0, max = sizeof control_keys / sizeof(sf::Text); i < max; i++)
		window->draw(control_keys[i]);
	
	window->draw(lines, sizeof lines / sizeof(sf::Vertex), sf::Quads);
}



void OPTIONS::show() 
{
	show_gui(true);
}

void OPTIONS::hide() 
{
	show_gui(false);
	ctx = &control_keys[5];
}

void OPTIONS::onCreate()
{
	ppX = window->getSize().x / 1920.0f;
	ppY = window->getSize().y / 1080.0f;

	keyboard.setScale(window->getSize().x / 1920.0f, window->getSize().y / 1080.0f);
	keyboard.setPosition(window->getSize().x / 2 - keyboard.getGlobalBounds().width / 2, window->getSize().y / 2);

	k.clear();
	fill_key_triggers();
	set_text();
	
}


void OPTIONS::fill_key_triggers()
{

	
#define OutlineThickness -4
	std::string tab[] = {
		"1","2","3","4","5","6","7","8","9","0","-","+","Backspace",
		"Q","W","E","R","T","Y","U","I","O","P","[","]","\\",
		"A","S","D","F","G","H","J","K","L",";",",","Enter",
		"Z","X","C","V","B","N","M",",",".","/","RShift",
		"LCTRL", "LALT","SPACE","RALT", "RCTRL", "LEFT", "DOWN","UP","RIGHT",
		"RShift" };


	for (std::size_t i = 0; i < 13; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(xx(53), yy(50))), tab[i]);
		k[i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (57 * ppX) - i * 0.5f, keyboard.getPosition().y + (36 * ppY));
		k[i].rec.setOutlineColor(sf::Color::Green);
		k[i].rec.setOutlineThickness(OutlineThickness);
		k[i].rec.setFillColor(sf::Color::Transparent);
	}

	for (std::size_t i = 0; i < 13; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), std::string(tab[i + 13]));
		k[13 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (87 * ppX) - i * 0.8f, keyboard.getPosition().y + (92 * ppY));
		k[13 + i].rec.setOutlineColor(sf::Color::Green);
		k[13 + i].rec.setOutlineThickness(OutlineThickness);
		k[13 + i].rec.setFillColor(sf::Color::Transparent);
	}

	for (std::size_t i = 0; i < 12; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), std::string(tab[i + 26]));
		k[26 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (99 * ppX) - i * 0.8f, keyboard.getPosition().y + (145 * ppY));
		k[26 + i].rec.setOutlineColor(sf::Color::Green);
		k[26 + i].rec.setOutlineThickness(OutlineThickness);
		k[26 + i].rec.setFillColor(sf::Color::Transparent);
	}

	for (std::size_t i = 0; i < 11; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), std::string(tab[i + 38]));
		k[38 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (126 * ppX) - i * 0.8f, keyboard.getPosition().y + (200 * ppY));
		k[38 + i].rec.setOutlineColor(sf::Color::Green);
		k[38 + i].rec.setOutlineThickness(OutlineThickness);
		k[38 + i].rec.setFillColor(sf::Color::Transparent);
	}


	k.emplace_back(sf::RectangleShape(sf::Vector2f(115 * ppX, 57 * ppY)), std::string(tab[49]));
	k[49].rec.setPosition(keyboard.getPosition().x, keyboard.getPosition().y + (257 * ppY));
	k[49].rec.setOutlineColor(sf::Color::Green);
	k[49].rec.setOutlineThickness(OutlineThickness);
	k[49].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(113 * ppX, 57 * ppY)), std::string(tab[50]));
	k[50].rec.setPosition(keyboard.getPosition().x + (123 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[50].rec.setOutlineColor(sf::Color::Green);
	k[50].rec.setOutlineThickness(OutlineThickness);
	k[50].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(280 * ppX, 57 * ppY)), std::string(tab[51]));
	k[51].rec.setPosition(keyboard.getPosition().x + (245 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[51].rec.setOutlineColor(sf::Color::Green);
	k[51].rec.setOutlineThickness(OutlineThickness);
	k[51].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(44 * ppX, 57 * ppY)), std::string(tab[52]));
	k[52].rec.setPosition(keyboard.getPosition().x + (536 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[52].rec.setOutlineColor(sf::Color::Green);
	k[52].rec.setOutlineThickness(OutlineThickness);
	k[52].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(44 * ppX, 57 * ppY)), std::string(tab[53]));
	k[53].rec.setPosition(keyboard.getPosition().x + (594 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[53].rec.setOutlineColor(sf::Color::Green);
	k[53].rec.setOutlineThickness(OutlineThickness);
	k[53].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(52 * ppX, 30 * ppY)), std::string(tab[54]));
	k[54].rec.setPosition(keyboard.getPosition().x + (653 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[54].rec.setOutlineColor(sf::Color::Green);
	k[54].rec.setOutlineThickness(OutlineThickness);
	k[54].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), std::string(tab[55]));
	k[55].rec.setPosition(keyboard.getPosition().x + (715 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[55].rec.setOutlineColor(sf::Color::Green);
	k[55].rec.setOutlineThickness(OutlineThickness);
	k[55].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), std::string(tab[56]));
	k[56].rec.setPosition(keyboard.getPosition().x + (715 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[56].rec.setOutlineColor(sf::Color::Green);
	k[56].rec.setOutlineThickness(OutlineThickness);
	k[56].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), std::string(tab[57]));
	k[57].rec.setPosition(keyboard.getPosition().x + (780 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[57].rec.setOutlineColor(sf::Color::Green);
	k[57].rec.setOutlineThickness(OutlineThickness);
	k[57].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(115 * ppX, 50 * ppY)), std::string(tab[58]));
	k[58].rec.setPosition(keyboard.getPosition().x, keyboard.getPosition().y + (200 * ppY));
	k[58].rec.setOutlineColor(sf::Color::Green);
	k[58].rec.setOutlineThickness(OutlineThickness);
	k[58].rec.setFillColor(sf::Color::Transparent);

	k[12].rec.setSize(sf::Vector2f(78 * ppX, 50 * ppY));  // Backspace
	k[37].rec.setSize(sf::Vector2f(95 * ppX, 50 * ppY));  // Enter
	k[48].rec.setSize(sf::Vector2f(125 * ppX, 50 * ppY)); // RShift

}

void OPTIONS::set_text()
{
	control_keys[0].setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[0].setString("flush");
	control_keys[0].setCharacterSize(yy(30));
	control_keys[0].setPosition(keyboard.getPosition().x - 2 * control_keys[0].getGlobalBounds().width, keyboard.getPosition().y);

	control_keys[1].setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[1].setString("rotate");
	control_keys[1].setCharacterSize(yy(30));
	control_keys[1].setPosition(keyboard.getPosition().x + 1.1f * control_keys[1].getGlobalBounds().width, keyboard.getPosition().y + 1.2f * keyboard.getGlobalBounds().height);

	control_keys[2].setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[2].setString("fast drop");
	control_keys[2].setCharacterSize(yy(30));
	control_keys[2].setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width + xx(30), keyboard.getPosition().y + 0.5f * keyboard.getGlobalBounds().height);

	control_keys[3].setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[3].setString("move left");
	control_keys[3].setCharacterSize(yy(30));
	control_keys[3].setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width - 2.0f * control_keys[3].getGlobalBounds().width, keyboard.getPosition().y - 0.3f * keyboard.getGlobalBounds().height);

	control_keys[4].setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[4].setString("move right");
	control_keys[4].setCharacterSize(yy(30));
	control_keys[4].setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width - 0.5f * control_keys[4].getGlobalBounds().width, keyboard.getPosition().y - 0.3f * keyboard.getGlobalBounds().height);
}

void OPTIONS::draw_lines(const sf::RectangleShape& start, const sf::RectangleShape& end, sf::Vertex* vertex, const sf::Color& color, int type, float thickness)
{
	sf::Vertex v[4];

	int x = 0;
	int y = 0;
	float cx = start.getPosition().x + start.getSize().x / 2;
	float cy = start.getPosition().y + start.getSize().y / 2;


	// 1 - LEFT
	// 2 - TOP
	// 3 - RIGHT
	// 4 - BOTTOM
	switch (type)
	{
	case 1:
		goto LEFT;
	case 2:
		goto TOP;
	case 3:
		goto RIGHT;
	case 4:
		goto BOTTOM;
	default:
		break;
	}


	// LEFT TOP start
	if (end.getPosition().x > start.getPosition().x + start.getSize().x && end.getPosition().y > start.getPosition().y + start.getSize().y)
	{

		if (std::rand() % 2)
		{
			goto LEFT;
		}
		else
		{
			goto TOP;
		};

	}
	// LEFT BOTTOM start
	else if (end.getPosition().x > start.getPosition().x && end.getPosition().y + end.getGlobalBounds().height < start.getPosition().y)
	{
		if (std::rand() % 2)
		{
			goto LEFT;
		}
		else
		{
			goto BOTTOM;
		};
	}
	// RIGHT TOP start
	else if (end.getPosition().x < start.getPosition().x && end.getPosition().y > start.getPosition().y + start.getSize().y)
	{
		if (std::rand() % 2)
		{
			goto TOP;
		}
		else
		{
			goto RIGHT;
		};
	}
	// RIGHT BOTTOM start
	else if (end.getPosition().x < start.getPosition().x && end.getPosition().y + end.getGlobalBounds().height < start.getPosition().y)
	{
		if (std::rand() % 2)
		{
			goto BOTTOM;
		}
		else
		{
			goto RIGHT;
		};
	}

	if (end.getPosition().x >= start.getPosition().x)
	{
		goto LEFT;
	}
	// RIGHT start
	else if (end.getPosition().x <= start.getPosition().x)
	{
		goto RIGHT;
	}
	// TOP start
	else if (end.getPosition().y >= start.getPosition().y)
	{
		goto TOP;
	}
	// BOTTOM start
	else if (end.getPosition().y <= start.getPosition().y)
	{
		goto BOTTOM;
	}

	// 1 - LEFT
	// 2 - TOP
	// 3 - RIGHT
	// 4 - BOTTOM
	switch (0)
	{
	case 0:
		break;
	case 1:
	LEFT:
		x = 1;
		y = 0;
		break;
	case 2:
	TOP:
		x = 0;
		y = 1;
		break;
	case 3:
	RIGHT:
		x = -1;
		y = 0;
		break;
	case 4:
	BOTTOM:
		x = 0;
		y = -1;
		break;
	default:
		break;
	}


	v[0].position = sf::Vector2f(cx + x * (start.getSize().x / 2.0f), cy + y * (start.getSize().y / 2.0f));
	x = abs(x);
	y = abs(y);

	v[1].position = sf::Vector2f(
		(y * v[0].position.x) + x * (end.getPosition().x + end.getSize().x / 2.0f),
		(x * v[0].position.y) + y * (end.getPosition().y + end.getSize().y / 2.0f));

	v[3].position = sf::Vector2f(
		(x * v[1].position.x) +
		y * (end.getPosition().x < start.getPosition().x ? end.getPosition().x + end.getSize().x : end.getPosition().x),
		(y * v[1].position.y) +
		x * (end.getPosition().y < start.getPosition().y ? end.getPosition().y + end.getSize().y : end.getPosition().y));

	if (end.getGlobalBounds().contains(v[1].position)) // p2 == p1
	{
		v[1].position.x = y * v[1].position.x +
			x * (end.getPosition().x < start.getPosition().x ? end.getPosition().x + end.getSize().x : end.getPosition().x);

		v[1].position.y = x * v[1].position.y +
			y * (end.getPosition().y < start.getPosition().y ? end.getPosition().y + end.getSize().y : end.getPosition().y);


		v[3].position = v[1].position;
	}

	v[2].position = v[1].position;

	sf::Vector2f dir = sf::Vector2f(v[1].position.x - v[0].position.x, v[1].position.y - v[0].position.y);
	dir /= sqrtf(dir.x * dir.x + dir.y * dir.y);

	sf::Vector2f per(-dir.y, dir.x);
	sf::Vector2f offset = thickness / 2.0f * per;

	vertex[0].position = v[0].position - offset;
	vertex[3].position = v[0].position + offset;

	vertex[1].position = v[1].position - offset;
	vertex[2].position = v[1].position + offset;

	dir = sf::Vector2f(v[3].position.x - v[2].position.x, v[3].position.y - v[2].position.y);
	dir /= sqrtf(dir.x * dir.x + dir.y * dir.y);

	per = sf::Vector2f(-dir.y, dir.x);
	offset = thickness / 2.0f * per;

	vertex[4].position = v[2].position - offset;
	vertex[7].position = v[2].position + offset;

	vertex[5].position = v[3].position - offset;
	vertex[6].position = v[3].position + offset;

	for (size_t i = 0; i < 7; i++)
		vertex[i].color = color;
}

void OPTIONS::erase_lines(sf::Vertex* vertex, std::size_t amount)
{
	ZeroMemory(vertex, sizeof(sf::Vertex)*amount);
}

void OPTIONS::startUp()
{
	window->addOnCreate(this);

	for (size_t i = 0, max = sizeof lines / sizeof(sf::Vertex); i < max; i++)
	{
		lines[i].position = sf::Vector2f(0, 0);
		lines[i].color = sf::Color::White;
	}
	

	ppX = window->getSize().x / 1920.0f;
	ppY = window->getSize().y / 1080.0f;
	
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

	sl_music = window->GUI_.CreateSliderList(0,0, 400);
	sl_music->setRelativePosition(gui::E_ANCHOR::A_TOP_LEFT, 100, 300);
	sl_music->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	sl_music->setTexture(AM->texture[AM_::E_TEXTURE::T_BSPHERE]);


	for (int i = 1; i <= 100; i++)
	{
		sl_music->add(std::move(std::to_string(i)));
	}
	

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
	window->GUI_.clear();

	keyboard.setTexture(AM->texture[AM_::E_TEXTURE::T_KEYBOARD]);
	keyboard.setScale(window->getSize().x / 1920.0f, window->getSize().y / 1080.0f);
	keyboard.setPosition(window->getSize().x / 2 - keyboard.getGlobalBounds().width / 2, window->getSize().y / 2);
	fill_key_triggers();
	set_text();
}


void OPTIONS::show_gui(bool show)
{
	if (show)
	{
		while (ShowCursor(TRUE) < 0);
		window->GUI_.add(b_Back);
		window->GUI_.add(b_Applay);
		window->GUI_.add(ddl_vm);
		window->GUI_.add(sl_music);
	}
	else
	{
		while (ShowCursor(FALSE) >= 0);
		window->GUI_.erase(b_Back);
		window->GUI_.erase(b_Applay);
		window->GUI_.erase(ddl_vm);
		window->GUI_.erase(sl_music);
	}
}





