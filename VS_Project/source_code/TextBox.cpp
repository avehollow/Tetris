#include "pch.h"
#include "TextBox.h"


gui::TextBox::TextBox(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text)
	: isActive(false)
	, active_color(sf::Color::Black)
	, idle_color(sf::Color(150, 150, 150, 200))
	, ppX(pos_x / window->getSize().x)
	, ppY(pos_y / window->getSize().y)
	, psX(size_x / window->getSize().x)
	, psY(size_y / window->getSize().y)
	, style(0)
{
	text_box.setFillColor(idle_color);
	text_box.setPosition(pos_x, pos_y);
	text_box.setSize(sf::Vector2f(size_x, size_y));

	text_box_2.setFillColor(idle_color);
	text_box_2.setPosition(pos_x, pos_y + size_y);
	text_box_2.setSize(sf::Vector2f(size_x, 3));



	tx.setString(text);
	tx.setFillColor(sf::Color::White);
	tx.setStyle(sf::Text::Style::Italic);
	tx.setCharacterSize(20);
	psF = (float)tx.getCharacterSize() / window->getSize().y;
	set_position_text();

	this->depth = depth;
}

void gui::TextBox::onRecreateWindow()
{
	text_box.setSize(sf::Vector2f(psX * window->getSize().x, psY * window->getSize().y));
	text_box_2.setSize(sf::Vector2f(text_box.getSize().x, 3));

	tx.setCharacterSize(psF * window->getSize().y);
	setPosition(ppX * window->getSize().x, ppY * window->getSize().y);
}

bool gui::TextBox::handleEvent(const sf::Event& event)
{
	if (handled_event)
	{
		text_box.setFillColor(idle_color);
		text_box_2.setFillColor(idle_color);
		return (isActive = false);
	}

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (text_box.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			isActive = !isActive;
			text_box.setFillColor(
				isActive ? active_color : idle_color);
			
			text_box_2.setFillColor(
				isActive ? active_color : idle_color);
		}
		else
		{
			isActive = false;
			text_box.setFillColor(idle_color);
			text_box_2.setFillColor(idle_color);
		}
	
		break;
	case sf::Event::TextEntered:
		if (isActive)
		{
			sf::String str = tx.getString();
			if (event.text.unicode == 8)
				tx.setString(str.substring(0, str.getSize() - 1));
			else if (event.text.unicode == 13) // enter = CRLF (Carriage return[13] + Line feed[10])
			{
				tx.setString(str + sf::String("\n"));
				
				if(tx.getGlobalBounds().height > text_box.getGlobalBounds().height)
					tx.setString(tx.getString().substring(0, tx.getString().getSize() - 1));
			}
			else
			{
				tx.setString(tx.getString() + sf::String(event.text.unicode));
				if (tx.getGlobalBounds().width > text_box.getGlobalBounds().width)
					tx.setString(tx.getString().substring(0, tx.getString().getSize() - 1));
			}
			
			set_position_text();
		}
		break;
	default:
		break;
	}

    return isActive;
}

void gui::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (style == 1)
		target.draw(text_box_2);
	else
		target.draw(text_box);

	target.draw(tx);
}

void gui::TextBox::setText(const sf::Text& text)
{
	psF = (float)text.getCharacterSize() / window->getSize().y;

	tx.setCharacterSize(text.getCharacterSize());
	tx.setFillColor(text.getFillColor());
	tx.setStyle(text.getStyle());
	tx.setFont(*text.getFont());
	tx.setString(text.getString());
	tx.setLineSpacing(text.getLineSpacing());
	tx.setLetterSpacing(text.getLetterSpacing());
	tx.setOutlineColor(text.getOutlineColor());
	tx.setOutlineThickness(text.getOutlineThickness());

	set_position_text();
}

void gui::TextBox::setString(const char* string)
{
	tx.setString(string);
	set_position_text();
}

void gui::TextBox::setFillColor(const sf::Color& color)
{
	text_box.setFillColor(color);
	text_box_2.setFillColor(color);
	idle_color = color;
}

void gui::TextBox::setActiveColor(const sf::Color& color)
{
	active_color = color;
}

void gui::TextBox::setPosition(float x, float y)
{
	ppX = x / window->getSize().x;
	ppY = y / window->getSize().y;

	text_box.setPosition(x, y);
	text_box_2.setPosition(x, y + text_box.getSize().y);
	set_position_text();
}

void gui::TextBox::setRelativePosition(E_ANCHOR anchor, float x, float y)
{
	sf::Vector2f p(calc_rel_pos(anchor, x, y));
	setPosition(p.x, p.y);
}

void gui::TextBox::setSize(const sf::Vector2f& size)
{
	psX = size.x / window->getSize().x;
	psY = size.y / window->getSize().y;

	text_box.setSize(size);
	text_box_2.setSize(sf::Vector2f(size.x, 3));

	set_position_text();
}

void gui::TextBox::setCharacterSize(unsigned int size)
{
	tx.setCharacterSize(size);
	set_position_text();
}

void gui::TextBox::setFont(const sf::Font& font)
{
	tx.setFont(font);
	set_position_text();
}

void gui::TextBox::setTexture(const sf::Texture& texture)
{
	text_box.setTexture(&texture);
	text_box.setFillColor(sf::Color::White);
	
	text_box_2.setTexture(&texture);
	text_box_2.setFillColor(sf::Color::White);
}

void gui::TextBox::setStyle(sf::Uint32 style)
{
	tx.setStyle(style);
}

void gui::TextBox::setBoxStyle(int style)
{
	this->style = style;
}
