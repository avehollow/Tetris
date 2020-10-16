#pragma once
#include "GUI.h"

namespace gui
{
	class Button : public gui__
	{

	public:
		Button(float pos_x, float pos_y, float size_x, float size_y, int depth = 0, const char* text = " ")noexcept;
		~Button();

		// Inherited via gui__
		virtual void onRecreateWindow() override;
		virtual bool handleEvent(const sf::Event& event) override;

		// Inherited via Drawable
		inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool Pressed();
		bool HoveOver();

		float			   getOutlineThickness() const { return shape.getOutlineThickness(); }
		sf::Vector2f	   getPosition()		 const { return shape.getPosition(); }
		sf::Vector2f	   getSize()			 const { return shape.getSize(); }
		inline std::string getString() const;

		void setText(const sf::Text&);
		void setString(const char*);
		void setFillColor(const sf::Color&);
		void setHoveOverColor(const sf::Color&);
		void setPosition(float x, float y);
		void setRelativePosition(E_ANCHOR anchor,float x, float y);
		void setSize(const sf::Vector2f&);
		void setOutlineColor(const sf::Color&);
		void setOutlineThickness(float  thickness);
		void setCharacterSize(unsigned int size);
		void setFont(const sf::Font&);
		void setTexture(const sf::Texture&);
		void setStyle(sf::Uint32 style);
		
		void setTextOffset(float ox, float oy);
		void move(float offsetX, float offsetY);


	
		int value;
	private:
		sf::RectangleShape shape;
		sf::Text text;


		sf::Color idle_color;
		sf::Color hoveover_color;

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

		enum BUTTONSTATE : char
		{
			B_NONE = 0,
			B_PRESSED = 1,
			B_HOVEOVER = 2
		};
		BUTTONSTATE state;



		// Auxiliary functions
		inline void set_position_text();
	};


	inline std::string Button::getString()const
	{
		return text.getString().toAnsiString();
	}

	inline void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(shape);
		target.draw(text);
	}

	inline void Button::set_position_text()
	{
		// If you need to position the text by the top - left of the actual content, 
		// set the sf::Text's origin to the local bounds' top - left.
		// It will need updating(to the bounds' top-left) whenever the content (string) changes.
		text.setOrigin(text.getLocalBounds().left, text.getLocalBounds().top);

		text.setPosition(
			shape.getPosition().x + shape.getSize().x / 2 - text.getGlobalBounds().width / 2,
			shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2
		);
	}

}