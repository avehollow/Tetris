#include "pch.h"
#include "GUI.h"

#include "DropDownList.h"
#include "SliderList.h"
#include "TextBox.h"

namespace gui
{
	GUI::GUI(sf::RenderWindow* window)
	{
		gui__::window = window;
	}

	GUI::~GUI()
	{
		for (gui__* g : gui)
		{
			delete g;
		}
	}

	void GUI::erase(void* const elem_of_gui)
	{
		
		gui__* ptr = reinterpret_cast<gui__*>(elem_of_gui);

		for (int i = gui.size() - 1; i >= 0; i--)
		{
			if (gui[i] == ptr)
			{
				delete gui[i];
				gui.erase(gui.begin() + i);
				break;
			}
		}
	}

	void GUI::reserve(const size_t _Newcapacity)
	{
		gui.reserve(_Newcapacity);
	}


	Button* GUI::CreateButton(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{
		Button* bt = new Button(pos_x, pos_y, size_x, size_y, depth, text);
		gui.push_back(dynamic_cast<gui__*>(bt));
		sort();
		return bt;
	}

	DropDownList* GUI::CreateDropDownList(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text, int max_show)
	{
		DropDownList* ddl = new DropDownList(pos_x, pos_y, size_x, size_y, depth, text, max_show);
		gui.push_back(dynamic_cast<gui__*>(ddl));
		sort();
		return ddl;
	}

	SliderList* GUI::CreateSliderList(float pos_x, float pos_y, float size_x, int depth, float radius, float size_y)
	{
		SliderList* sl = new SliderList(pos_x, pos_y, size_x, depth, radius, size_y);
		gui.push_back(dynamic_cast<gui__*>(sl));
		sort();
		return sl;
	}

	TextBox* GUI::CreateTextBox(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{

		TextBox* tb = new TextBox(pos_x, pos_y, size_x, size_y, depth, text);
		gui.push_back(dynamic_cast<gui__*>(tb));
		sort();
		return tb;
	}
	
	sf::Vector2f gui__::calc_rel_pos(E_ANCHOR anchor, float x, float y)
	{
		float xx = 0.0f;
		float yy = 0.0f;
		switch (anchor)
		{
		case gui::A_TOP_LEFT:
			xx = x;
			yy = y;
			break;
		case gui::A_TOP_RIGHT:
			xx = window->getSize().x - x;
			yy = y;
			break;
		case gui::A_BOTTOM_LEFT:
			xx = x;
			yy = window->getSize().y - y;
			break;
		case gui::A_BOTTOM_RIGHT:
			xx = window->getSize().x - x;
			yy = window->getSize().y - y;
			break;
		case gui::A_CENTER_LEFT:
			xx = x;
			yy = window->getSize().y / 2 + y;
			break;
		case gui::A_CENTER_RIGHT:
			xx = window->getSize().x - x;
			yy = window->getSize().y / 2 + y;
			break;
		case gui::A_CENTER_TOP:
			xx = window->getSize().x / 2 + x;
			yy = y;
			break;
		case gui::A_CENTER_BOTTOM:
			xx = window->getSize().x / 2 + x;
			yy = window->getSize().y - y;
			break;
		case gui::A_CENTER:
			xx = window->getSize().x / 2 + x;
			yy = window->getSize().y / 2 + y;
			break;
		default:
			break;
		}
		return sf::Vector2f(xx, yy);
	}

	bool gui__::handled_event = false;
	sf::RenderWindow* gui__::window = nullptr;
}
