#pragma once

namespace gui
{
	enum E_ANCHOR
	{
		A_TOP_LEFT = 0,
		A_TOP_RIGHT = 1,
		A_BOTTOM_LEFT,
		A_BOTTOM_RIGHT,
		A_CENTER_LEFT,
		A_CENTER_RIGHT,
		A_CENTER_TOP,
		A_CENTER_BOTTOM,
		A_CENTER
	};

	class Button;
	class DropDownList;
	class SliderList;
	class TextBox;

	class gui__;

	class GUI
	{
	public:
		GUI(sf::RenderWindow* window);
		GUI(const GUI&)  = delete;
		GUI(const GUI&&) = delete;
		~GUI();

		inline void onRecreateWindow()const;
		inline void handleEvent(const sf::Event& event)const;

		inline void draw() const;

		Button* CreateButton(float pos_x, float pos_y, float size_x, float size_y, int depth = 0, const char* text = " ");
		DropDownList* CreateDropDownList(float pos_x, float pos_y, float size_x, float size_y, int depth = 0, const char* text = " ", int max_show = 8);
		SliderList* CreateSliderList(float pos_x, float pos_y, float size_x, int depth = 0, float radius = 15, float size_y = 3);
		TextBox* CreateTextBox(float pos_x, float pos_y, float size_x, float size_y, int depth = 0, const char* text = " ");
		

	private:
		std::vector<gui__*> gui;

		inline void sort();
	};


	class gui__: public sf::Drawable
	{
		friend class GUI;
	public:
		int getDepth()const { return depth; }
		//void setDepth(int depth) { this->depth = depth; } do prawid³owego dzia³ania trzeba jeszcze wywo³aæ funkcjê sort z klasy GUI

		virtual ~gui__() = default;
	protected:
		static sf::RenderWindow* window;
		static bool handled_event;
		int depth;

		virtual void onRecreateWindow() = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

		inline void getDeltaMouse(int* dtX, int* dtY);

		sf::Vector2f calc_rel_pos(E_ANCHOR anchor, float x, float y);
	};

	
}







inline void gui::gui__::getDeltaMouse(int* dtX, int* dtY)
{
	static int px = 0;
	static int py = 0;

	static int px_p = 0;
	static int py_p = 0;

	px = sf::Mouse::getPosition(*window).x;
	py = sf::Mouse::getPosition(*window).y;

	*dtX = px - px_p;
	*dtY = py - py_p;

	px_p = px;
	py_p = py;
}



inline void gui::GUI::sort()
{
	std::sort(gui.begin(), gui.end(), [](const gui__* lhs, const gui__* rhs) { return lhs->getDepth() > rhs->getDepth(); });
}

inline void gui::GUI::draw() const
{
	for (int i = gui.size() - 1; i >= 0; i--)
	{
		gui__::window->draw(*gui[i]);
	}
}

inline void gui::GUI::onRecreateWindow()const
{
	for (auto& g : gui)
	{
		g->onRecreateWindow();
	}
}

inline void gui::GUI::handleEvent(const sf::Event& event) const
{
	gui__::handled_event = false;
	for (auto& g : gui)
	{
		if (g->handleEvent(event))
			gui__::handled_event = true;
	}
}
