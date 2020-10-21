#include "pch.h"
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
		
		button.setRadius(radius);
		button.setOrigin(radius, radius);
		button.setPosition(posX, posY + ((int)sizeY / 2));

		button.setOutlineColor(sf::Color(77, 77, 77));
		button.setOutlineThickness(-3);

		text.setCharacterSize(20);
		text.setPosition(posX + sizeX + radius + 1, button.getPosition().y - text.getGlobalBounds().height / 2);
		
		this->depth = depth;
	}

	SliderList::~SliderList()
	{
	}

	bool SliderList::handleEvent(const sf::Event& event)
	{
		
		static bool hove_over = false;
		static bool pressed   = false;
	
		static bool ki = false;	

		if (handled_event)
		{
			button.setFillColor(idle_color);
			return hove_over = pressed = ki = false;
		}
		
		int dt_x = 0;
		int dt_y = 0;

		sf::Vector2f pos;

		float length = 0.0f;

		const size_t SIZE = strings.size();
		const float pos_x = slider.getPosition().x;
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			pressed = true;
			break;
		case sf::Event::MouseMoved:
			pos.x = fabs(sf::Mouse::getPosition(*window).x - button.getPosition().x);
			pos.y = fabs(sf::Mouse::getPosition(*window).y - button.getPosition().y);
			length = sqrtf((pos.x * pos.x) + (pos.y * pos.y)); // length of vector

			if (length <= button.getRadius())
			{
				button.setFillColor(hoveover_color);
				hove_over = true;
			}
			else
			{
				button.setFillColor(idle_color);
				hove_over = false;
			}

			getDeltaMouse(&dt_x, &dt_y);
			if (ki)
			{
				if (dt_x > 50)
				{
					button.setPosition(pos_x + slider.getSize().x, button.getPosition().y);
					ki = false;
					idx = SIZE - 1;
					text.setString(strings[idx]);
					break;
				}
				if (dt_x < -50)
				{
					button.setPosition(pos_x, button.getPosition().y);	
					idx = 0;
					text.setString(strings[idx]);
					ki = false;
					break;
				}
				
			}

			if (pressed && hove_over)
			{
				ki = true;

				float p = slider.getSize().x / ((float)SIZE - 1);
				
				button.setPosition(sf::Mouse::getPosition(*window).x, button.getPosition().y);
			
				
				if (button.getPosition().x > pos_x + slider.getSize().x)
					button.setPosition(pos_x + slider.getSize().x, button.getPosition().y);
	
				else if (button.getPosition().x < pos_x )
					button.setPosition(pos_x, button.getPosition().y);
				
				idx = (button.getPosition().x - pos_x + (p / 2)) / p;
				text.setString(strings[idx]);
			}

			break;
		default:
			pressed = false;
			ki = false;
			
			break;
		}

		return hove_over;
	}

	void SliderList::add(const char* text)
	{
		strings.push_back(text);
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
		button.setPosition(x, y + ((int)slider.getSize().y / 2));
		this->text.setPosition(x + slider.getSize().x + button.getRadius() + 1, slider.getPosition().y - (this->text.getGlobalBounds().height / 2) - 1);
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

	void SliderList::onRecreateWindow()
	{
		slider.setSize(sf::Vector2f(window->getSize().x * psX, window->getSize().y * psY));
		button.setRadius(window->getSize().y * psR);
		button.setOrigin(button.getRadius(), button.getRadius());
		text.setCharacterSize(window->getSize().y * psF);
		
		setPosition(window->getSize().x * ppX, window->getSize().y * ppY);
	}

}


