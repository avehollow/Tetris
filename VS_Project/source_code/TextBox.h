#pragma once
#include "GUI.h"


namespace gui
{
	class TextBox : public gui__
	{
	public:
		TextBox(float pos_x, float pos_y, float size_x, float size_y, int depth = 0, const char* text = " ");
		~TextBox() {};

		inline sf::String getString()const;

		// Inherited via gui__
		virtual void onRecreateWindow() override;
		virtual bool handleEvent(const sf::Event& event) override;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void setText(const sf::Text&);
		void setString(const char*);
		void setFillColor(const sf::Color&);
		void setActiveColor(const sf::Color&);
		void setPosition(float x, float y);
		void setRelativePosition(E_ANCHOR anchor, float x, float y);
		void setSize(const sf::Vector2f&);
		void setCharacterSize(unsigned int size);
		void setFont(const sf::Font&);
		void setTexture(const sf::Texture&);
		void setStyle(sf::Uint32 style);
		// 0 or 1
		void setBoxStyle(int style);

	private:
		bool isActive;

		int style;

		sf::RectangleShape text_box;
		sf::RectangleShape text_box_2;
		sf::Text tx;

		sf::Color active_color;
		sf::Color idle_color;

		float offset_x;
		float offset_y;

		// percentage position [0 - 1]
		float ppX;
		float ppY;

		// percentage size [0 - 1]
		float psX;
		float psY;

		// percentage font size (character size) [0 - 1]
		double psF;

		inline void set_position_text();
	};


	inline void TextBox::set_position_text()
	{
		// If you need to position the text by the top - left of the actual content, 
		// set the sf::Text's origin to the local bounds' top - left.
		// It will need updating(to the bounds' top-left) whenever the content (string) changes.
		tx.setOrigin(tx.getLocalBounds().left, tx.getLocalBounds().top);

		tx.setPosition(
			text_box.getPosition().x + text_box.getSize().x / 2 - tx.getGlobalBounds().width / 2,
			text_box.getPosition().y + text_box.getSize().y / 2 - tx.getGlobalBounds().height / 2
		);
	}

	inline sf::String TextBox::getString() const
	{
		return tx.getString();
	}
}
