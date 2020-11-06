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

		gui.reserve(200);
		buttons.reserve(100);
		dropDownLists.reserve(10);
		sliderLists.reserve(25);
		textBoxs.reserve(50);
	}

	GUI::~GUI()
	{
		
	}

	void GUI::erase(void* const elem_of_gui)
	{
		
		gui__* ptr = reinterpret_cast<gui__*>(elem_of_gui);

		for (int i = gui.size() - 1; i >= 0; i--)
		{
			if (gui[i] == ptr)
			{
				gui.erase(gui.begin() + i);
				break;
			}
		}
	}




	Button* GUI::CreateButton(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{
		buttons.emplace_back(pos_x, pos_y, size_x, size_y, depth, text);
		bad_way();
		sort();
		return &buttons.back();
	}

	DropDownList* GUI::CreateDropDownList(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text, int max_show)
	{		
		dropDownLists.emplace_back(pos_x, pos_y, size_x, size_y, depth, text, max_show);
		bad_way();
		sort();
		return &dropDownLists.back();
	}

	SliderList* GUI::CreateSliderList(float pos_x, float pos_y, float size_x, int depth, float radius, float size_y)
	{
		sliderLists.emplace_back(pos_x, pos_y, size_x, depth, radius, size_y);
		bad_way();
		sort();
		return &sliderLists.back();
	}

	TextBox* GUI::CreateTextBox(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{
		textBoxs.emplace_back(pos_x, pos_y, size_x, size_y, depth, text);
		bad_way();
		sort();
		return &textBoxs.back();
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

void gui::GUI::bad_way()
{
	gui.clear();
	for (auto& x : buttons)
		gui.emplace_back(dynamic_cast<gui__*>(&x));

	for (auto& x : dropDownLists)
		gui.emplace_back(dynamic_cast<gui__*>(&x));

	for (auto& x : sliderLists)
		gui.emplace_back(dynamic_cast<gui__*>(&x));

	for (auto& x : textBoxs)
		gui.emplace_back(dynamic_cast<gui__*>(&x));

}