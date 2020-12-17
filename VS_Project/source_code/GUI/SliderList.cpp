#include "../pch.h"
#include "SliderList.h"

namespace gui
{
	SliderList::SliderList(float posX, float posY, float sizeX, int depth, float radius, float sizeY)
		: ppX(posX / window->getSize().x)
		, ppY(posY / window->getSize().y)
		, psX(sizeX / window->getSize().x)
		, psY(sizeY / window->getSize().y)
		, psR(radius / window->getSize().y)
		, psF(20.0f / window->getSize().y)
		, idx(0)
		, idle_color(sf::Color::White)
		, hoveover_color(sf::Color::Red)
	{
		slider.setPosition(posX, posY);
		slider.setSize(sf::Vector2f(sizeX, sizeY));
		slider.setFillColor(sf::Color(44, 44, 44));	
		
		collision.setPosition(posX, posY - radius);
		collision.setSize(sf::Vector2f(sizeX, radius * 2.0f));
		collision.setFillColor(sf::Color::Transparent);
		collision.setOutlineColor(sf::Color::Red);
		collision.setOutlineThickness(-2);
		
		
		button.setRadius(radius);
		button.setOrigin(radius, radius);
		button.setPosition(posX, posY + ((int)sizeY / 2));

		button.setOutlineColor(sf::Color(77, 77, 77));
		button.setOutlineThickness(-3);

		text.setCharacterSize(20);
		text.setPosition(posX + sizeX + radius + 1, button.getPosition().y - text.getGlobalBounds().height / 2);
		
		this->depth = depth;
		bHoveover = false;
	}

	SliderList::~SliderList()
	{
	}

	bool SliderList::handleEvent(const sf::Event& event)
	{
		bHoveover = false;

		sf::Vector2i vi = window->mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(*window)));
		if (handled_event)
		{
			button.setFillColor(idle_color);
		}
		else if (collision.getGlobalBounds().contains(sf::Vector2f(vi)))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				button.setPosition(vi.x, button.getPosition().y);
				button.setFillColor(hoveover_color);
				bHoveover = true;

				float p = slider.getSize().x / ((float)strings.size() - 1);
				idx = (button.getPosition().x - slider.getPosition().x + (p / 2)) / p;
				text.setString(strings[idx]);
			}
		}
		else
		{
			button.setFillColor(idle_color);
		}

		return bHoveover;
	}

	void SliderList::add(const char* text)
	{
		strings.push_back(text);
		this->text.setString(strings[0]);
		this->text.setPosition(this->text.getPosition().x, slider.getPosition().y - (this->text.getGlobalBounds().height / 2) - 1);
	}

	void SliderList::add(std::string&& text)
	{
		strings.push_back(std::forward<std::string&&>(text));
		this->text.setString(strings[0]);
		this->text.setPosition(this->text.getPosition().x, slider.getPosition().y - (this->text.getGlobalBounds().height / 2) - 1);
	}

	void SliderList::add(const std::initializer_list<const char*>& strings)
	{
		for (const auto& tx : strings)
			this->strings.push_back(tx);
		
		text.setString(this->strings[0]);
		this->text.setPosition(this->text.getPosition().x, slider.getPosition().y - (this->text.getGlobalBounds().height / 2) - 1);
	}

	void SliderList::setFillColor(const sf::Color& color)
	{
		idle_color = color;
	}

	void SliderList::setHoveOverColor(const sf::Color& color)
	{
		hoveover_color = color;
	}

	void SliderList::setPointCount(std::size_t count)
	{
		button.setPointCount(count);
	}

	void SliderList::setStyleText(sf::Uint32 style)
	{
		text.setStyle(style);
	}

	void SliderList::setFont(const sf::Font& font)
	{
		text.setFont(font);
	}

	void SliderList::setPosition(float x, float y)
	{
		ppX = x / window->getSize().x;
		ppY = y / window->getSize().y;

		slider.setPosition(x, y);
		button.setPosition(slider.getPosition().x + slider.getSize().x * idx / (float)strings.size(), y + slider.getSize().y / 2.0f);
		//button.setPosition(x, y + ((int)slider.getSize().y / 2));
		this->text.setPosition(x + slider.getSize().x + button.getRadius() + 1, slider.getPosition().y - (this->text.getGlobalBounds().height / 2) - 1);
		collision.setPosition(x, y - button.getRadius());
	}

	void SliderList::setRelativePosition(E_ANCHOR anchor, float x, float y)
	{
		sf::Vector2f p(calc_rel_pos(anchor, x, y));
		setPosition(p.x, p.y);
	}

	void SliderList::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
		psF = (float)size / window->getSize().y;
	}

	void SliderList::setTexture(const sf::Texture& texture)
	{
		button.setTexture(&texture);
		idle_color = sf::Color::White;
	}

	void SliderList::setOutlineColor(const sf::Color& color)
	{
		button.setOutlineColor(color);
	}

	void SliderList::setOutlineThickness(float thickness)
	{
		button.setOutlineThickness(thickness);
	}

	void SliderList::setCurrentValue(std::size_t idx)
	{
		if (idx < strings.size())
		{
			this->idx = idx;
			text.setString(strings[idx]);
			button.setPosition(slider.getPosition().x + slider.getSize().x * idx / (float)strings.size(), button.getPosition().y);
		}
	}

	void SliderList::onRecreateWindow()
	{
		slider.setSize(sf::Vector2f(window->getSize().x * psX, window->getSize().y * psY));
		button.setRadius(window->getSize().y * psR);
		button.setOrigin(button.getRadius(), button.getRadius());
		text.setCharacterSize(window->getSize().y * psF);
		collision.setSize(sf::Vector2f(slider.getSize().x, button.getRadius() * 2.0f ));
		setPosition(window->getSize().x * ppX, window->getSize().y * ppY);
	}

}


