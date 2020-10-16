#pragma once

#include "GUI.h"

namespace gui
{
	class SliderList : public gui__
	{
	public:
		SliderList(float posX, float posY, float sizeX, int depth = 0, float radius = 15, float sizeY = 3);
		~SliderList();

		// Inherited via gui__
		virtual void onRecreateWindow() override;
		virtual bool handleEvent(const sf::Event&) override;

		// Inherited via Drawable
		inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		inline int getCurrentIndex()const;

		void add(const char* text);
		void add(const std::initializer_list<const char*>& strings);

		void setFillColor(const sf::Color&);
		void setHoveOverColor(const sf::Color&);
		void setPointCount(std::size_t count);
		void setStyleText(sf::Uint32 style);
		void setFont(const sf::Font&);
		void setPosition(float x, float y);
		void setRelativePosition(E_ANCHOR anchor, float x, float y);
		void setCharacterSize(unsigned int size);
		void setTexture(const sf::Texture&);
		void setOutlineColor(const sf::Color&);
		void setOutlineThickness(float thickness);
		
	private:
		sf::RectangleShape slider;
		sf::CircleShape button;

		sf::Text text;
		std::vector<const char*> strings;
		sf::Color idle_color;
		sf::Color hoveover_color;

		float ppX;
		float ppY;

		float psX;
		float psY;

		float psR;

		float psF;

		int idx;
		

	};
	
	inline void gui::SliderList::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(slider);
		target.draw(button);
		target.draw(text);
	}

	inline int SliderList::getCurrentIndex() const
	{
		return idx;
	}

}

