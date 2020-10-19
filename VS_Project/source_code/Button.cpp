#include "pch.h"
#include "Button.h"

namespace gui
{
	Button::Button(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* tx)noexcept
		: state(BUTTONSTATE::B_NONE)
		, idle_color(sf::Color(40, 41, 41, 150))
		, hoveover_color(sf::Color(67, 69, 69, 150))
		, offset_x(0.0f)
		, offset_y(0.0f)
		, value(0)
		, ppX(pos_x / window->getSize().x)
		, ppY(pos_y / window->getSize().y)
		, psX(size_x / window->getSize().x)
		, psY(size_y / window->getSize().y)
	{
		this->depth = depth;
		this->is_visible = true;

		shape.setSize(sf::Vector2f(size_x, size_y));
		shape.setFillColor(idle_color);
		setPosition(pos_x, pos_y);
		

		text.setString(tx);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Style::Bold);
		text.setCharacterSize(20);
		psF = (float)text.getCharacterSize() / window->getSize().y;

		set_position_text();
	}


	void Button::setTextOffset(float ox, float oy)
	{
		offset_x = ox;
		offset_y = oy;
		
		text.move(ox, oy);
	}


	void Button::move(float offsetX, float offsetY)
	{
		shape.move(offsetX, offsetY);
		set_position_text();

		ppX = shape.getPosition().x / window->getSize().x;
		ppY = shape.getPosition().y / window->getSize().y;
	}


	void Button::setText(const sf::Text& t)
	{
		psF = (float)t.getCharacterSize() / window->getSize().y;

		text.setCharacterSize(t.getCharacterSize());
		text.setFillColor(t.getFillColor());
		text.setStyle(t.getStyle());
		text.setFont(*t.getFont());
		text.setString(t.getString());
		text.setLineSpacing(t.getLineSpacing());
		text.setLetterSpacing(t.getLetterSpacing());
		text.setOutlineColor(t.getOutlineColor());
		text.setOutlineThickness(t.getOutlineThickness());

		set_position_text();
	}

	void Button::setString(const char* t)
	{
		text.setString(t);
		set_position_text();
	}


	void Button::setFillColor(const sf::Color& color)
	{
		idle_color = color;
		shape.setFillColor(color);
	}

	void Button::setHoveOverColor(const sf::Color& color)
	{
		hoveover_color = color;
		shape.setFillColor(color);
	}

	void Button::setPosition(float x, float y)
	{
		ppX = x / window->getSize().x;
		ppY = y / window->getSize().y;
		
		shape.setPosition(x, y);
		set_position_text();
	}

	void Button::setRelativePosition(E_ANCHOR anchor, float x, float y)
	{
		sf::Vector2f p(calc_rel_pos(anchor, x, y));
		setPosition(p.x,p.y);
	}
	
	void Button::setSize(const sf::Vector2f& size)
	{
		psX = size.x / window->getSize().x;
		psY = size.y / window->getSize().y;
		
		shape.setSize(size);
		set_position_text();
	}

	void Button::setOutlineColor(const sf::Color& color)
	{
		shape.setOutlineColor(color);
	}

	void Button::setOutlineThickness(float thickness)
	{
		shape.setOutlineThickness(thickness);
	}

	void Button::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
		psF = (float)size / window->getSize().y;
		set_position_text();
	}

	void Button::setFont(const sf::Font& font)
	{
		text.setFont(font);
		set_position_text();
	}

	void Button::setTexture(const sf::Texture& texture)
	{
		shape.setTexture(&texture);
		idle_color = sf::Color::White;
	}

	void Button::setStyle(sf::Uint32 style)
	{
		text.setStyle(style);
		set_position_text();
	}

	bool Button::handleEvent(const sf::Event& event)
	{
		if (!handled_event && shape.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonReleased:
				if (event.key.code == sf::Mouse::Left)
				{
					state = BUTTONSTATE::B_PRESSED;
				}
				break;
			default:
				shape.setFillColor(hoveover_color);
				state = BUTTONSTATE::B_HOVEOVER;
				break;
			}
		}
		else
		{
			shape.setFillColor(idle_color);
			state = BUTTONSTATE::B_NONE;
		}
		return (bool)state;
	}

	bool Button::Pressed()
	{
		if (state == BUTTONSTATE::B_PRESSED)
		{
			state = BUTTONSTATE::B_NONE;
			return true;
		}
		return false;
	}

	bool Button::HoveOver()
	{
		if (state == BUTTONSTATE::B_HOVEOVER)
			return true;
		else		
			return false;
	}

	void Button::onRecreateWindow()
	{
		shape.setPosition(window->getSize().x * ppX, window->getSize().y * ppY);
		shape.setSize(sf::Vector2f(window->getSize().x * psX, window->getSize().y * psY));

		text.setCharacterSize(window->getSize().y * psF);
		set_position_text();
		setTextOffset(offset_x, offset_y);
	}


	Button::~Button()
	{
	}
}


