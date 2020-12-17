#include "pch.h"
#include "Options.h"
#include "GUI/DropDownList.h"
#include "GUI/SliderList.h"
#include "Resource.h"

// AVE LOOK a better approach is the inline function
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
		if ( ddl_vm->curr_value			   != -1				  &&
			 vm[ddl_vm->curr_value].width  != window->getSize().x &&
			 vm[ddl_vm->curr_value].height != window->getSize().y)
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

		} // if

		saveSettings();
	}
	
	/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
	
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i vi = window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
		for (size_t i = 0, max = sizeof control_keys / sizeof(ControlKey); i < max; i++)
		{
			control_keys[i].text.setFillColor(sf::Color::White);
			if (control_keys[i].text.getGlobalBounds().contains(sf::Vector2f(vi)))
			{
				control_keys[i].text.setFillColor(sf::Color::Magenta);
				key_chosen = i; 
				AM->sound[AM_::E_SOUND::S_CLICK_2].play();
				// return has to be here
				return state;
			}
		}

		if (key_chosen != -1)
		{
			for (auto& i : k)
			{
				if (i.rec.getGlobalBounds().contains(sf::Vector2f(vi)))
				{

					sf::RectangleShape b;
					b.setPosition(control_keys[key_chosen].text.getPosition());
					b.setSize(sf::Vector2f(control_keys[key_chosen].text.getGlobalBounds().width, control_keys[key_chosen ].text.getGlobalBounds().height));

					for (size_t k = 0, max = sizeof control_keys / sizeof(ControlKey); k < max; k++)
					{
						if (control_keys[k].ptr == &i)
						{
							control_keys[k].ptr = nullptr;
							ms.control_keys[k] = sf::Keyboard::Unknown;
							erase_lines(lines + k * 8, 8);

						}
					}

					sf::RectangleShape end;
					end.setSize(i.rec.getSize());
					switch (key_chosen)
					{
					case 0:
						linkABusing2lines(b, i.rec, lines + key_chosen * 8, sf::Color(255,0,0,200), 1, 3.0f);
						break;														
					case 1:															
						linkABusing2lines(b, i.rec, lines + key_chosen * 8, sf::Color(0,255,0,200), 4, 3.0f);
						break;														
					case 2:															
						linkABusing2lines(b, i.rec, lines + key_chosen * 8, sf::Color::Blue, 3, 3.0f);
						break;														
					case 3:															
						end.setPosition(sf::Vector2f(i.rec.getPosition().x, i.rec.getPosition().y + yy(4)));
						linkABusing2lines(b, end, lines + key_chosen * 8, sf::Color(0,255,0,200), 2, 3.0f);
						break;														
					case 4:		
						end.setPosition(sf::Vector2f(i.rec.getPosition().x, i.rec.getPosition().y - yy(4)));
						linkABusing2lines(b, end, lines + key_chosen * 8, sf::Color(255,0,0,200), 2, 3.0f);
						break;
					default:
						break;
					}

					control_keys[key_chosen].ptr = &i;
					ms.control_keys[key_chosen] = i.code;
					key_chosen = -1;
					AM->sound[AM_::E_SOUND::S_CLICK_1].play();
					break;
				}
			}
			key_chosen = -1;
		}
	}

	return state;
}


void OPTIONS::update(const float& d)
{
	AM->setMusicVolume(sl_music->getCurrentIdx());
	AM->setSoundVolume(sl_sound->getCurrentIdx());
}

void OPTIONS::render() const
{
	window->draw(keyboard);
	for (auto& i : k)
		window->draw(i.rec);

	window->draw(lines, sizeof lines / sizeof(sf::Vertex), sf::Quads);
	
	for (size_t i = 0, max = sizeof control_keys / sizeof(ControlKey); i < max; i++)
		window->draw(control_keys[i].text);
	
	window->draw(tx_mv);
	window->draw(tx_sv);
}



void OPTIONS::show() 
{
	show_gui(true);
	window->GUI_.setIdle();
}

void OPTIONS::hide() 
{
	show_gui(false);
	for (size_t i = 0, max = sizeof control_keys / sizeof(ControlKey); i < max; i++)
		control_keys[i].text.setFillColor(sf::Color::White);
	
	key_chosen = -1;

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
	linkControlKeys();
}


void OPTIONS::fill_key_triggers()
{

	
#define OutlineThickness 0
	short tab[] = {
		sf::Keyboard::Num1, //0
		sf::Keyboard::Num2, //1
		sf::Keyboard::Num3, //2
		sf::Keyboard::Num4,	//3
		sf::Keyboard::Num5, //4
		sf::Keyboard::Num6,	//5
		sf::Keyboard::Num7,	//6
		sf::Keyboard::Num8,	//7
		sf::Keyboard::Num9,	//8
		sf::Keyboard::Num0,	//9
		sf::Keyboard::Hyphen,	//10
		sf::Keyboard::Equal,	//11
		sf::Keyboard::Backspace,//12
		sf::Keyboard::Q,	//13
		sf::Keyboard::W,	//14
		sf::Keyboard::E,	//15
		sf::Keyboard::R,	//16
		sf::Keyboard::T,	//17
		sf::Keyboard::Y,	//18
		sf::Keyboard::U,	//19
		sf::Keyboard::I,	//20
		sf::Keyboard::O,	//21
		sf::Keyboard::P,	//22
		sf::Keyboard::LBracket,	//23
		sf::Keyboard::RBracket,	//24
		sf::Keyboard::Backslash,//25
		sf::Keyboard::A,	//26
		sf::Keyboard::S,	//27
		sf::Keyboard::D,	//28
		sf::Keyboard::F,	//29
		sf::Keyboard::G,	//30
		sf::Keyboard::H,	//31
		sf::Keyboard::J,	//32
		sf::Keyboard::K,	//33
		sf::Keyboard::L,	//34
		sf::Keyboard::Semicolon,//35
		sf::Keyboard::Quote,	//36
		sf::Keyboard::Enter,	//37
		sf::Keyboard::Z,	//38
		sf::Keyboard::X,	//39
		sf::Keyboard::C,	//40
		sf::Keyboard::V,	//41
		sf::Keyboard::B,	//42
		sf::Keyboard::N,	//43
		sf::Keyboard::M,	//44
		sf::Keyboard::Comma,	//45
		sf::Keyboard::Period,	//46
		sf::Keyboard::Slash,	//47
		sf::Keyboard::RShift,	//48
		sf::Keyboard::LControl,	//49
		sf::Keyboard::LAlt,		//50
		sf::Keyboard::Space,	//51
		sf::Keyboard::RAlt,		//52
		sf::Keyboard::RControl,	//53
		sf::Keyboard::Left,		//54
		sf::Keyboard::Down,		//55
		sf::Keyboard::Up,		//56
		sf::Keyboard::Right,	//57
		sf::Keyboard::RShift	//58
	};

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
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), tab[i + 13]);
		k[13 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (87 * ppX) - i * 0.8f, keyboard.getPosition().y + (92 * ppY));
		k[13 + i].rec.setOutlineColor(sf::Color::Green);
		k[13 + i].rec.setOutlineThickness(OutlineThickness);
		k[13 + i].rec.setFillColor(sf::Color::Transparent);
	}

	for (std::size_t i = 0; i < 12; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), tab[i + 26]);
		k[26 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (99 * ppX) - i * 0.8f, keyboard.getPosition().y + (145 * ppY));
		k[26 + i].rec.setOutlineColor(sf::Color::Green);
		k[26 + i].rec.setOutlineThickness(OutlineThickness);
		k[26 + i].rec.setFillColor(sf::Color::Transparent);
	}

	for (std::size_t i = 0; i < 11; i++)
	{
		k.emplace_back(sf::RectangleShape(sf::Vector2f(53 * ppX, 50 * ppY)), tab[i + 38]);
		k[38 + i].rec.setPosition(keyboard.getPosition().x + i * (59 * ppX) + (126 * ppX) - i * 0.8f, keyboard.getPosition().y + (200 * ppY));
		k[38 + i].rec.setOutlineColor(sf::Color::Green);
		k[38 + i].rec.setOutlineThickness(OutlineThickness);
		k[38 + i].rec.setFillColor(sf::Color::Transparent);
	}


	k.emplace_back(sf::RectangleShape(sf::Vector2f(115 * ppX, 57 * ppY)), tab[49]);
	k[49].rec.setPosition(keyboard.getPosition().x, keyboard.getPosition().y + (257 * ppY));
	k[49].rec.setOutlineColor(sf::Color::Green);
	k[49].rec.setOutlineThickness(OutlineThickness);
	k[49].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(113 * ppX, 57 * ppY)), tab[50]);
	k[50].rec.setPosition(keyboard.getPosition().x + (123 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[50].rec.setOutlineColor(sf::Color::Green);
	k[50].rec.setOutlineThickness(OutlineThickness);
	k[50].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(280 * ppX, 57 * ppY)), tab[51]);
	k[51].rec.setPosition(keyboard.getPosition().x + (245 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[51].rec.setOutlineColor(sf::Color::Green);
	k[51].rec.setOutlineThickness(OutlineThickness);
	k[51].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(44 * ppX, 57 * ppY)), tab[52]);
	k[52].rec.setPosition(keyboard.getPosition().x + (536 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[52].rec.setOutlineColor(sf::Color::Green);
	k[52].rec.setOutlineThickness(OutlineThickness);
	k[52].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(44 * ppX, 57 * ppY)), tab[53]);
	k[53].rec.setPosition(keyboard.getPosition().x + (594 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[53].rec.setOutlineColor(sf::Color::Green);
	k[53].rec.setOutlineThickness(OutlineThickness);
	k[53].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(52 * ppX, 30 * ppY)), tab[54]);
	k[54].rec.setPosition(keyboard.getPosition().x + (653 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[54].rec.setOutlineColor(sf::Color::Green);
	k[54].rec.setOutlineThickness(OutlineThickness);
	k[54].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), tab[55]);
	k[55].rec.setPosition(keyboard.getPosition().x + (715 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[55].rec.setOutlineColor(sf::Color::Green);
	k[55].rec.setOutlineThickness(OutlineThickness);
	k[55].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), tab[56]);
	k[56].rec.setPosition(keyboard.getPosition().x + (715 * ppX), keyboard.getPosition().y + (257 * ppY));
	k[56].rec.setOutlineColor(sf::Color::Green);
	k[56].rec.setOutlineThickness(OutlineThickness);
	k[56].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(55 * ppX, 30 * ppY)), tab[57]);
	k[57].rec.setPosition(keyboard.getPosition().x + (780 * ppX), keyboard.getPosition().y + (285 * ppY));
	k[57].rec.setOutlineColor(sf::Color::Green);
	k[57].rec.setOutlineThickness(OutlineThickness);
	k[57].rec.setFillColor(sf::Color::Transparent);

	k.emplace_back(sf::RectangleShape(sf::Vector2f(115 * ppX, 50 * ppY)), tab[58]);
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
	control_keys[0].text.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[0].text.setString("flush");
	control_keys[0].text.setCharacterSize(yy(30));
	control_keys[0].text.setPosition(keyboard.getPosition().x - 2 * control_keys[0].text.getGlobalBounds().width, keyboard.getPosition().y);

	control_keys[1].text.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[1].text.setString("rotate");
	control_keys[1].text.setCharacterSize(yy(30));
	control_keys[1].text.setPosition(keyboard.getPosition().x + 1.15f * control_keys[1].text.getGlobalBounds().width, keyboard.getPosition().y + 1.2f * keyboard.getGlobalBounds().height);

	control_keys[2].text.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[2].text.setString("fast drop");
	control_keys[2].text.setCharacterSize(yy(30));
	control_keys[2].text.setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width + xx(100), keyboard.getPosition().y + 0.5f * keyboard.getGlobalBounds().height);

	control_keys[3].text.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[3].text.setString("move left");
	control_keys[3].text.setCharacterSize(yy(30));
	control_keys[3].text.setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width - 2.0f * control_keys[3].text.getGlobalBounds().width, keyboard.getPosition().y - 0.3f * keyboard.getGlobalBounds().height);

	control_keys[4].text.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	control_keys[4].text.setString("move right");
	control_keys[4].text.setCharacterSize(yy(30));
	control_keys[4].text.setPosition(keyboard.getPosition().x + keyboard.getGlobalBounds().width - 0.2f * control_keys[4].text.getGlobalBounds().width, keyboard.getPosition().y - 0.3f * keyboard.getGlobalBounds().height);

	tx_sv.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	tx_sv.setString("Sound Volume");
	tx_sv.setCharacterSize(yy(30));
	tx_sv.setPosition(sl_sound->getGlobalPosition().x + sl_sound->getSize().x / 2.0f - tx_sv.getGlobalBounds().width / 2.0f,
		sl_sound->getGlobalPosition().y - yy(60));

	tx_mv.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	tx_mv.setString("Music Volume");
	tx_mv.setCharacterSize(yy(30));
	tx_mv.setPosition(sl_music->getGlobalPosition().x + sl_music->getSize().x / 2.0f - tx_mv.getGlobalBounds().width / 2.0f,
		sl_music->getGlobalPosition().y - yy(60));
}

void OPTIONS::linkControlKeys()
{
	for (size_t i = 0, max = sizeof control_keys / sizeof(ControlKey); i < max; i++)
	{
		sf::RectangleShape b;
		b.setPosition(control_keys[i].text.getPosition());
		b.setSize(sf::Vector2f(control_keys[i].text.getGlobalBounds().width, control_keys[i].text.getGlobalBounds().height));

		sf::RectangleShape end;
		switch (Settings::KEY_ACTION(i))
		{
		case Settings::KEY_ACTION::FLUSH:
			if(control_keys[i].ptr != nullptr)
				linkABusing2lines(b, control_keys[i].ptr->rec, lines + i * 8, sf::Color(255,0,0,200), 1, 3.0f);
			break;

		case Settings::KEY_ACTION::ROTATE:
			if (control_keys[i].ptr != nullptr)
				linkABusing2lines(b, control_keys[i].ptr->rec, lines + i * 8, sf::Color(0, 255, 0, 200), 4, 3.0f);
			break;

		case Settings::KEY_ACTION::FAST_DROP:
			if (control_keys[i].ptr != nullptr)
				linkABusing2lines(b, control_keys[i].ptr->rec, lines + i * 8, sf::Color::Blue, 3, 3.0f);
			break;

		case Settings::KEY_ACTION::MOVE_LEFT:
			if (control_keys[i].ptr != nullptr)
			{
			    end.setSize(control_keys[i].ptr->rec.getSize());
				end.setPosition(control_keys[i].ptr->rec.getPosition().x, control_keys[i].ptr->rec.getPosition().y + yy(4));
				linkABusing2lines(b, end, lines + i * 8, sf::Color(0,255,0,200), 2, 3.0f);
				//linkABusing2lines(b, control_keys[i].ptr->rec, lines + i * 8, sf::Color::Green, 2, 3.0f);
			}
			break;

		case Settings::KEY_ACTION::MOVE_RIGHT:
			if (control_keys[i].ptr != nullptr)
			{
			    end.setSize(control_keys[i].ptr->rec.getSize());
				end.setPosition(control_keys[i].ptr->rec.getPosition().x, control_keys[i].ptr->rec.getPosition().y - yy(4));
				linkABusing2lines(b, end, lines + i * 8, sf::Color(255,0,0,200), 2, 3.0f);
				//linkABusing2lines(b, control_keys[i].ptr->rec, lines + i * 8, sf::Color::Red, 2, 3.0f);
			}
			break;
		default:
			break;
		}
	}
}

void OPTIONS::linkABusing2lines(const sf::RectangleShape& A, const sf::RectangleShape& B, sf::Vertex* vertex, const sf::Color& color, int type, float thickness)
{
#define start A
#define end B
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

	for (size_t i = 0; i <= 7; i++)
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

	sl_music = window->GUI_.CreateSliderList(0, 0, 400);
	sl_music->setRelativePosition(gui::E_ANCHOR::A_TOP_LEFT, 100, 200);
	sl_music->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	sl_music->setTexture(AM->texture[AM_::E_TEXTURE::T_BSPHERE]);

	sl_sound = window->GUI_.CreateSliderList(0, 0, 400);
	sl_sound->setRelativePosition(gui::E_ANCHOR::A_TOP_LEFT, 100, 100);
	sl_sound->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	sl_sound->setTexture(AM->texture[AM_::E_TEXTURE::T_BSPHERE]);

	for (int i = 0; i <= 100; i++)
	{
		sl_music->add(std::move(std::to_string(i)));
		sl_sound->add(std::move(std::to_string(i)));
	}
	sl_music->setCurrentValue(40);
	sl_sound->setCurrentValue(30);

	AM->setMusicVolume(40);
	AM->setSoundVolume(30);

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
		ddl_vm->add((std::to_string(vm[i].width) + "x" + std::to_string(vm[i].height) + "x" + std::to_string(vm[i].bitsPerPixel)).c_str(), i);

	ddl_vm->curr_value = -1;

	show_gui(false);
	window->GUI_.clear();

	keyboard.setTexture(AM->texture[AM_::E_TEXTURE::T_KEYBOARD]);
	keyboard.setScale(window->getSize().x / 1920.0f, window->getSize().y / 1080.0f);
	keyboard.setPosition(window->getSize().x / 2 - keyboard.getGlobalBounds().width / 2, window->getSize().y / 2);
	fill_key_triggers();
	set_text();
	key_chosen = -1;


	ms.control_keys[Settings::FLUSH] = sf::Keyboard::Z;
	ms.control_keys[Settings::ROTATE] = sf::Keyboard::Space;
	ms.control_keys[Settings::FAST_DROP] = sf::Keyboard::Down;
	ms.control_keys[Settings::MOVE_LEFT] = sf::Keyboard::Left;
	ms.control_keys[Settings::MOVE_RIGHT] = sf::Keyboard::Right;

	control_keys[Settings::FLUSH].ptr = &k[38]; //z
	control_keys[Settings::ROTATE].ptr = &k[51]; //space
	control_keys[Settings::FAST_DROP].ptr = &k[55]; //down
	control_keys[Settings::MOVE_LEFT].ptr = &k[54]; //left;
	control_keys[Settings::MOVE_RIGHT].ptr = &k[57]; //right;


	// 1b = 1 error with open
	// 2b = 1 error with movement
	// 3b = 1 error with audio
	// 4b = 1 error with graphics
	std::byte result = loadSettings();
	if (std::to_integer<int>(~result & std::byte{ 0b1 }))
	{
		if (std::to_integer<int>(~result & std::byte{ 0b10 }))
		{
			for (size_t k = 0, max = sizeof control_keys / sizeof(ControlKey); k < max; k++)
			{
				if (ms.control_keys[k] == sf::Keyboard::Unknown)
					control_keys[k].ptr = nullptr;
			}
			// AVE LOOK bad loop ! this loop runs/perform 300 times
			for (auto& key : k)
			{
				for (size_t k = 0, max = sizeof control_keys / sizeof(ControlKey); k < max; k++)
				{
					if (key.code == ms.control_keys[k])
						control_keys[k].ptr = &key;

				}
			}
		}
	}


	linkControlKeys();
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
		window->GUI_.add(sl_sound);
	}
	else
	{
		while (ShowCursor(FALSE) >= 0);
		window->GUI_.erase(b_Back);
		window->GUI_.erase(b_Applay);
		window->GUI_.erase(ddl_vm);
		window->GUI_.erase(sl_music);
		window->GUI_.erase(sl_sound);
	}
}

std::byte OPTIONS::saveSettings() const
{

	std::byte result{0b0000'0000};
	std::ofstream output_data("settings.java", std::ios::binary | std::ios::out);


	// 1b = 1 error with open
	// 2b = 1 error with movement
	// 3b = 1 error with audio
	// 4b = 1 error with graphics
	if (output_data.is_open())
	{
		output_data.write((const char*)&ms, sizeof(Settings::Movement));
		if (!output_data.good())
			result |= std::byte{ 0b0010 };
		
		int idx = sl_music->getCurrentIdx();
		output_data.write((const char*)&idx, sizeof(int));
		if (!output_data.good())
			result |= std::byte{ 0b0100 };
		
		idx = sl_sound->getCurrentIdx();
		output_data.write((const char*)&idx, sizeof(int));
		if (!output_data.good())
			result |= std::byte{ 0b0100 };
		

		output_data.write((const char*)&ddl_vm->curr_value, sizeof(int));
		if (!output_data.good())
			result |= std::byte{ 0b1000 };
	}
	else
	{
		result |= std::byte{ 0b0001 };
	}

	output_data.close();


	//if (output_data.is_open())
	//	output_data.write((const char*)&ms, sizeof(Settings::Movement));
	//else
	//	result |= std::byte{ 0b1 };

	
	return result;
}

std::byte OPTIONS::loadSettings()
{

	std::byte result{ 0b0000'0000 };
	std::ifstream input_data("settings.java", std::ios::binary | std::ios::in);

	// 1b = 1 error with open
	// 2b = 1 error with movement
	// 3b = 1 error with audio
	// 4b = 1 error with graphics
	if (input_data.is_open())
	{
		input_data.read((char*)&ms, sizeof(Settings::Movement));
		if (!input_data.good())
			result |= std::byte{ 0b0010 };

		std::size_t idx;
		input_data.read((char*)&idx, sizeof(int));
		if (!input_data.good())
			result |= std::byte{ 0b0100 };
		sl_music->setCurrentValue(idx);

		idx = 0;
		input_data.read((char*)&idx, sizeof(int));
		if (!input_data.good())
			result |= std::byte{ 0b0100 };
		sl_sound->setCurrentValue(idx);
			
		idx = 0;
		input_data.read((char*)&idx, sizeof(idx));
		if (!input_data.good())
			result |= std::byte{ 0b1000 };

		if (idx < 0 || idx >= ddl_vm->getListSize() )
			idx = 0;
		
		ddl_vm->curr_value = idx;
		ddl_vm->setLabelString((std::to_string(vm[idx].width) + "x" + std::to_string(vm[idx].height) + "x" + std::to_string(vm[idx].bitsPerPixel)).c_str());
		// AVE TODO create proper window
		// Incorrect GUI implementation does not allow window resizing in this function
		// because the loadSettings is called from startUp, the GUI is not set correctly when re-creating the window.
		// window->create(vm[idx], "Tetris", sf::Style::Fullscreen);
		// look at WORLD.cpp ini function
	}
	else
	{
		result |= std::byte{ 0b0001 };
	}

	input_data.close();

	//if (input_data.is_open())
	//	input_data.read((char*)&ms, sizeof(Settings::Movement));
	//else
	//	result |= std::byte{ 0b1 };


	return result;
}





