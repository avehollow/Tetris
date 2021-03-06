#include "../pch.h"
#include "GUI.h"

#include "DropDownList.h"
#include "SliderList.h"
#include "TextBox.h"

namespace gui
{
	GUI::GUI(sf::RenderWindow* window)
	{
		gui__::window = window;

		gui.reserve(50);
		buttons.reserve(20);
		dropDownLists.reserve(3);
		sliderLists.reserve(5);
		textBoxs.reserve(5);
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

	void GUI::add(void* const elem_of_gui)
	{
		gui__* ptr = reinterpret_cast<gui__*>(elem_of_gui);
		gui.push_back(ptr);
		sort();
	}




	Button* GUI::CreateButton(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{
		buttons.emplace_back(pos_x, pos_y, size_x, size_y, depth, text);
		update_gui();
		sort();
		return &buttons.back();
	}

	DropDownList* GUI::CreateDropDownList(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text, int max_show)
	{		
		dropDownLists.emplace_back(pos_x, pos_y, size_x, size_y, depth, text, max_show);
		update_gui();
		sort();
		return &dropDownLists.back();
	}

	SliderList* GUI::CreateSliderList(float pos_x, float pos_y, float size_x, int depth, float radius, float size_y)
	{
		sliderLists.emplace_back(pos_x, pos_y, size_x, depth, radius, size_y);
		update_gui();
		sort();
		return &sliderLists.back();
	}

	TextBox* GUI::CreateTextBox(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	{
		textBoxs.emplace_back(pos_x, pos_y, size_x, size_y, depth, text);
		update_gui();
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
} // namespace gui

void gui::GUI::update_gui()
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

void gui::GUI::onRecreateWindow()
{
	for (auto& x : buttons)
		x.onRecreateWindow();

	for (auto& x : dropDownLists)
		x.onRecreateWindow();

	for (auto& x : sliderLists)
		x.onRecreateWindow();

	for (auto& x : textBoxs)
		x.onRecreateWindow();
}