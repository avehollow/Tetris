#include "pch.h"
#include "DropDownList.h"

namespace gui
{
	DropDownList::DropDownList(float pos_x, float pos_y, float size_x, float size_y, int depth, const char* text, int max_show)
		: ppX_label(pos_x / window->getSize().x)
		, ppY_label(pos_y / window->getSize().y)
		, psX_label((size_x - size_y) / window->getSize().x)
		, psY_label(size_y / window->getSize().y)
		, button(pos_x + size_x - size_y, pos_y, size_y, size_y, depth, " ")
		, show_list(false)
		, curr_value(0)
		, beg (0)
		, end(abs(max_show))
		, max_show(abs(max_show))
	{

		stripe_background.setFillColor(sf::Color(45,45,45,200));
		stripe.setFillColor(sf::Color::Color(170,170,170,200));
	

		button.setFillColor(sf::Color(255, 0, 0, 100));
		button.setOutlineColor(sf::Color::Black);
		button.setOutlineThickness(-2);
		
		label.setSize(sf::Vector2f(size_x - size_y - button.getOutlineThickness(), size_y)); // OutlineThickness is negative
		label.setOutlineThickness(-2);
		label.setOutlineColor(sf::Color::Black);
		label.setFillColor(sf::Color::Transparent);


		curr_text.setString(text);
		curr_text.setCharacterSize(20);
		psF_main = (float)curr_text.getCharacterSize() / window->getSize().y;

		// SetPostion must be after label.setSize()
		setPosition(pos_x, pos_y);
		SetPositionText();

		this->depth = depth;
	}

	bool DropDownList::handleEvent(const sf::Event& event)
	{
		const size_t SIZE = list.size();

		if (handled_event)
		{
			for (int i = beg; (i <= end) && (i < SIZE); i++)
				list[i].handleEvent(event);
			
			return false;
		}

		bool hove_over = false;
		if (show_list)
			hove_over = collision.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

		
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			button.handleEvent(event);
			if (button.Pressed())
				show_list = !show_list;

			break;
		case sf::Event::MouseWheelMoved:
			if (show_list && hove_over && event.mouseWheel.delta < 0)
			{
				if (end + 1 < SIZE)
				{
					end++;
					beg++;
					for (size_t i = 0; (i < SIZE); i++)
						list[i].move(0, -list[0].getSize().y);


					stripe.setPosition(
						stripe.getPosition().x,
						(button.getPosition().y + button.getSize().y) + ((stripe_background.getSize().y) * ((float)beg / (SIZE)))
					);
				}
			}
			if (show_list && hove_over && event.mouseWheel.delta > 0)
			{
				if (beg - 1 >= 0)
				{
					beg--;
					end--;
					for (size_t i = 0; (i < SIZE); i++)
						list[i].move(0, +list[0].getSize().y);

					stripe.setPosition(
						stripe.getPosition().x,
						(button.getPosition().y + button.getSize().y) + ((stripe_background.getSize().y) * ((float)beg / (SIZE - 1)))
					);
				}
			}
			break;
		default:
			break;
		}
		

		if (show_list)
		{
			// handleEvent must be at the end because of beg & end
			for (int i = beg; (i <= end) && (i < SIZE); i++)
			{
				list[i].handleEvent(event);

				if (list[i].Pressed())
				{
					curr_text.setString(list[i].getString());
					SetPositionText();
					curr_value = list[i].value;
					show_list = false;
					break;
				}
			}
		}

		return hove_over;
	}

	void DropDownList::add(const char* text, int value_)
	{
		float size_x = label.getSize().x + button.getOutlineThickness(); // OutlineThickness is negative
		float size_y = label.getSize().y; 

		const size_t SIZE = list.size() + 1;
		list.emplace_back(
			label.getPosition().x, 
			label.getPosition().y + (size_y * SIZE),
			size_x,
			size_y, 
			depth,
			text
		);
		list.back().value = value_;
		list.back().setFont(font_list);

		

		if (SIZE <= max_show)
		{
			stripe_background.setSize(sf::Vector2f(size_y, size_y * SIZE));
			collision.setSize(sf::Vector2f(size_x + button.getSize().x, size_y * SIZE));
		}
		
		if (max_show < SIZE)
			stripe.setSize(sf::Vector2f(size_y, stripe_background.getSize().y * ((float)max_show / SIZE)));
		else
			stripe.setSize(sf::Vector2f(size_y, stripe_background.getSize().y));
		
	}

	void DropDownList::add(const std::initializer_list<const char*>& strings,const std::initializer_list<int>& values_)
	{
		const size_t SIZE = values_.size();
		int i = 0;
		for (const auto& tx : strings)
		{
			if (i < SIZE)
			{
				add(tx, *values_.begin()+i);
				i++;
			}
			else
			{
				add(tx, 0);
			}
		}
	}

	bool DropDownList::erase(const char* text)
	{
		sf::Vector2f pos;
		sf::Vector2f pos2;
		
		float size_x = label.getSize().x + button.getOutlineThickness(); // OutlineThickness is negative
		float size_y = label.getSize().y;

		bool res = false;

		size_t i = 0;
		for (i = 0; i < list.size(); i++)
		{
			if (strcmp(text, list[i].getString().c_str()) == 0)
			{
				pos = list[i].getPosition();
				list.erase(list.begin() + i);
		
				res = true;
				break;
			}
		}
		
		const size_t SIZE = list.size();
		for ( ; i < SIZE ; i++)
		{
			pos2 = list[i].getPosition();
			list[i].setPosition(pos.x, pos.y);
			pos = pos2;
		}

		if (SIZE <= max_show + 1)
		{
			stripe_background.setSize(sf::Vector2f(size_y, size_y * SIZE));
			collision.setSize(sf::Vector2f(size_x, size_y * SIZE));
		}

		if (max_show < SIZE)
			stripe.setSize(sf::Vector2f(size_y, stripe_background.getSize().y * ((float)max_show / SIZE)));
		else
			stripe.setSize(sf::Vector2f(size_y, stripe_background.getSize().y));

		return res;
	}

	void DropDownList::setFillColorList(const sf::Color& color)
	{
		label.setFillColor(color);
		for (auto& bt : list)
			bt.setFillColor(color);
		
	}

	void DropDownList::setFillColorBt(const sf::Color& color)
	{
		button.setFillColor(color);
	}

	void DropDownList::setHoveOverColorList(const sf::Color& color)
	{
		for (auto& bt : list)
			bt.setHoveOverColor(color);
	}

	void DropDownList::setHoveOverColorBt(const sf::Color& color)
	{
		button.setHoveOverColor(color);
	}

	void DropDownList::setFontList(const sf::Font& font)
	{
		font_list = font;
		for (auto& bt : list)
			bt.setFont(font);
	}

	void DropDownList::setFontMain(const sf::Font& font)
	{
		curr_text.setFont(font);
		SetPositionText();
	}

	void DropDownList::setFont(const sf::Font& font)
	{
		font_list = font;
		curr_text.setFont(font);
		for (auto& bt : list)
			bt.setFont(font);
		
		SetPositionText();
	}

	void DropDownList::setCharacterSizeList(float size)
	{
		for (auto& bt : list)
			bt.setCharacterSize(size);
	}

	void DropDownList::setCharacterSizeMain(float size)
	{
		curr_text.setCharacterSize(size);
		SetPositionText();

		psF_main = (float)size / window->getSize().y;
	}

	void DropDownList::setCharacterSize(float size)
	{
		for (auto& bt : list)
			bt.setCharacterSize(size);

		curr_text.setCharacterSize(size);
		SetPositionText();
	}

	void DropDownList::setStyleList(sf::Uint32 style)
	{
		for (auto& bt : list)
			bt.setStyle(style);
	}

	void DropDownList::setStyleMain(sf::Uint32 style)
	{
		curr_text.setStyle(style);
		SetPositionText();
	}

	void DropDownList::setStyle(sf::Uint32 style)
	{
		for (auto& bt : list)
			bt.setStyle(style);

		curr_text.setStyle(style);
		SetPositionText();
	}


	
	void DropDownList::setPosition(float x, float y)
	{
		ppX_label = x / window->getSize().x;
		ppY_label = y / window->getSize().y;
		
		float size_x = label.getSize().x + button.getOutlineThickness(); // OutlineThickness is negative
		float size_y = label.getSize().y;


		label.setPosition(x, y);
		button.setPosition(x + size_x, y);
		SetPositionText();

		collision.setPosition(x, y + size_y);

		const size_t SIZE = list.size();
		for (int i = 0; i < SIZE ; i++)
		{
			list[i].setPosition(x, y + ((i+1) * size_y));
		}
		beg = 0;
		end = max_show - 1;

			
		stripe_background.setPosition(button.getPosition().x, y + size_y);
		stripe.setPosition(button.getPosition().x, y + size_y);
	}

	void DropDownList::setRelativePosition(E_ANCHOR anchor, float x, float y)
	{
		sf::Vector2f p(calc_rel_pos(anchor, x, y));
		setPosition(p.x, p.y);
	}


	bool DropDownList::setStringList(const char* oldt, const char* newt)
	{
		bool res = false;
		for (auto& bt : list)
		{
			if (bt.getString().compare(oldt) == 0)
			{
				res = true;
				bt.setString(newt);
				break;
			}
		}
		return res;
	}

	void DropDownList::setOutlineColor(const sf::Color& color)
	{
		label.setOutlineColor(color);
		button.setOutlineColor(color);
	}

	void DropDownList::setOutlineThickness(float thickness)
	{
		button.setOutlineThickness(-2);
		label.setSize(sf::Vector2f(label.getSize().x - label.getSize().y - button.getOutlineThickness(), label.getSize().y));
		label.setOutlineThickness(-2);
	}

	void DropDownList::setTextureList(const sf::Texture& texture)
	{
		for (auto& bt : list)
			bt.setTexture(texture);
	}

	void DropDownList::setTextureMain(const sf::Texture& texture)
	{
		label.setTexture(&texture);
	}

	void DropDownList::setTextureBt(const sf::Texture& texture)
	{
		button.setTexture(texture);
	}

	void DropDownList::onRecreateWindow()
	{
		// Must be first
		label.setSize(sf::Vector2f(window->getSize().x * psX_label - button.getOutlineThickness(), window->getSize().y * psY_label));

		float size_x = label.getSize().x + button.getOutlineThickness();
		float size_y = label.getSize().y;

		for (auto& bt : list)
			bt.onRecreateWindow();
		button.onRecreateWindow();

		// must be after button.onRecreateWindow()
		const size_t SIZE = list.size();
		if (max_show < SIZE)
		{
			stripe_background.setSize(sf::Vector2f(button.getSize().x, max_show * size_y));
			stripe.setSize(sf::Vector2f(button.getSize().x, stripe_background.getSize().y * ((float)max_show / SIZE)));
			collision.setSize(sf::Vector2f(size_x + button.getSize().x, size_y * max_show));
		}
		else
		{
			stripe_background.setSize(sf::Vector2f(button.getSize().x, size_y * SIZE));
			stripe.setSize(sf::Vector2f(button.getSize().x, stripe_background.getSize().y));
			collision.setSize(sf::Vector2f(size_x + button.getSize().x, size_y * SIZE));
		}

		curr_text.setCharacterSize(psF_main * window->getSize().y);

		// setPostion must be at the end
		setPosition(window->getSize().x * ppX_label, window->getSize().y * ppY_label);
		SetPositionText();
	}

	DropDownList::~DropDownList()
	{
	}
}
