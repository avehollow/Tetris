#pragma once
#include "Button.h"

namespace gui
{
	class DropDownList : public gui__
	{
	public:
		DropDownList(
			float pos_x,
			float pos_y,
			float size_x,
			float size_y,
			int depth = 0,
			const char* text = "",
			int max_show = 8
		);
		virtual ~DropDownList();

		// Inherited via gui__
		virtual void onRecreateWindow() override;
		virtual bool handleEvent(const sf::Event&) override;

		// Inherited via Drawable
		inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		sf::Vector2f	   getGlobalPosition()	 const { return label.getPosition(); }
		std::string		   getCurrentString()    const { return curr_text.getString(); }

		void add(const char* text, int value_ = 0);
		void add(const std::initializer_list<const char*>& strings, const std::initializer_list<int>& values_ = {0});
		bool erase(const char* text);
		void setFillColorList(const sf::Color&);
		void setFillColorBt(const sf::Color&);
		void setHoveOverColorList(const sf::Color&);
		void setHoveOverColorBt(const sf::Color&);
		void setFontList(const sf::Font&);
		void setFontMain(const sf::Font&);
		void setFont(const sf::Font&);
		void setCharacterSizeList(float size);
		void setCharacterSizeMain(float size);
		void setCharacterSize(float size);
		void setStyleList(sf::Uint32 style);
		void setStyleMain(sf::Uint32 style);
		void setStyle(sf::Uint32 style);
		void setPosition(float x, float y);
		void setRelativePosition(E_ANCHOR anchor, float x, float y);
		bool setStringList(const char* oldt, const char* newt);
		void setOutlineColor(const sf::Color&);
		void setOutlineThickness(float  thickness);
		void setTextureList(const sf::Texture&);
		void setTextureMain(const sf::Texture&);
		void setTextureBt(const sf::Texture&);



		int curr_value;
	private:
		std::vector<Button> list;

		sf::Text curr_text;
		sf::RectangleShape label;

	
		sf::RectangleShape stripe_background;
		sf::RectangleShape stripe;

		sf::RectangleShape collision;
	
		Button button;

		sf::Font font_list;

		// percentage position [0 - 1]
		float ppX_label;
		float ppY_label;

		// percentage size [0 - 1]
		float psX_label;
		float psY_label;

		// percentage font size (character size) [0 - 1]
		double psF_main;

		bool show_list;

		int beg;
		int end;
		int max_show;


		// Auxiliary functions
		inline void SetPositionText();
	};




	inline void DropDownList::SetPositionText()
	{
		// If you need to position the text by the top - left of the actual content, 
		// set the sf::Text's origin to the local bounds' top - left.
		// It will need updating(to the bounds' top-left) whenever the content (string) changes.
		curr_text.setOrigin(curr_text.getLocalBounds().left, curr_text.getLocalBounds().top);

		curr_text.setPosition(
			label.getPosition().x + label.getSize().x / 2 - curr_text.getGlobalBounds().width / 2,
			label.getPosition().y + label.getSize().y / 2 - curr_text.getGlobalBounds().height / 2
		);
	}

	inline void DropDownList::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(label);
		target.draw(button);
		target.draw(curr_text);

		if (show_list)
		{
			const size_t SIZE = list.size();
			for (int i = beg; (i <= end) && (i < SIZE); i++)
			{
				target.draw(list[i]);
			}

			target.draw(stripe_background);
			target.draw(stripe);
		}

	}

}
