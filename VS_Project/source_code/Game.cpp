#include "pch.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "Options.h"

GAME game;

extern OPTIONS options;

ISTATE* GAME::handleInput(const sf::Event& event)
{
	return (this->*curr_hdl_fun)(event);
}


void GAME::update(const float& tt)
{
	if (!bPause && !bGameOver)
	{

		bGameOver = score = tetromino.update(tt);
		if (bGameOver)
		{
			show_gameover_menu(true);
			set_gameovermode();
		}
	}
	else 
	{
		tetromino.pause();
	}

}

void GAME::render()const
{

	//window->draw(background_game);

	//tetromino.draw(window);

	//if (bPause)
	//{
	//	window->draw(background_pause);
	//}
	//else if (bGameOver)
	//{
	//	window->draw(background_gameover);
	//	window->draw(txGameOver);
	//	window->draw(txScore);
	//	window->draw(txDate);
	//}

	window->draw(background_game);

	tetromino.draw(window);

	(this->*curr_ren_fun)();
}

void GAME::show()
{
	show_pause_menu(bPause);
}

void GAME::hide()
{
	show_pause_menu(false);
}

void GAME::show_pause_menu(bool show)
{
	/*b_Back->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);*/
	ShowCursor(show);
	if (show)
	{
		window->GUI_.add(b_Back);
		window->GUI_.add(b_Options);
		window->GUI_.add(b_Exit);
		set_pausemode();
	}
	else
	{
		window->GUI_.erase(b_Back);
		window->GUI_.erase(b_Options);
		window->GUI_.erase(b_Exit);
		set_standardmode();
	}
}	


void GAME::show_gameover_menu(bool show)
{
	//b_Exit2->visible(show);
	//b_PlayAgain->visible(show);
	//txb_Nick->visible(show);
	ShowCursor(show);
	if (show)
	{
		window->GUI_.add(b_PlayAgain);
		window->GUI_.add(b_Exit2);
		window->GUI_.add(txb_Nick);
		txScore.setString(" your score :" + std::to_string(score));
	}
	else
	{
		window->GUI_.erase(b_PlayAgain);
		window->GUI_.erase(b_Exit2);
		window->GUI_.erase(txb_Nick);
	}
}

void GAME::update_hightscore()
{

	std::fstream out;
	std::vector<std::tuple<std::array<char, 20>, int, std::array<char, 20>>> h;
	h.resize(11);

	for (auto& k : h)
	{
		for (size_t i = 0; i < 20; i++)
		{
			std::get<0>(k)[i] = 0;
			std::get<2>(k)[i] = 0;
		}
		std::get<1>(k) = 0;
	};

	out.open("x@Ew.java", std::ios::binary | std::ios::in);
	if (out.is_open())
	{
		for (size_t i = 0; !out.eof() && (i < 10); i++)
		{
			int size = 0;
			out.read((char*)&size, sizeof(int));
			out.read((char*)std::get<0>(h[i]).data(), sizeof(char) * size);
			out.read((char*)&std::get<1>(h[i]), sizeof(int));
			out.read((char*)&size, sizeof size);
			out.read((char*)std::get<2>(h[i]).data(), sizeof(char) * size);
		}
	}

	std::get<1>(h[10]) = score;

	std::string nick = txb_Nick->getString();
	for (int i = 0, size = nick.size(); i < size && i < 20; i++)
		std::get<0>(h[10])[i] = nick[i];
	
	
	nick = txDate.getString();
	for (int i = 0, size = nick.size(); i < size && i < 20; i++)
		std::get<2>(h[10])[i] = nick[i];
	

	std::sort(
		h.begin(),
		h.end(),
		[]( auto const& lhs, auto const& rhs) { return std::get<1>(lhs) > std::get<1>(rhs); }
	);
	out.close();

	out.open("x@Ew.java", std::ios::binary | std::ios::out);

	for (size_t i = 0; i < 10; i++)
	{
		int size = std::get<0>(h[i]).size();
		out.write((const char*)&size, sizeof(int));
		out.write((const char*)std::get<0>(h[i]).data(), sizeof(char) * size);
		out.write((const char*)&std::get<1>(h[i]), sizeof(int));
		size = std::get<2>(h[i]).size();
		out.write((const char*)&size, sizeof size);
		out.write((const char*)std::get<2>(h[i]).data(), sizeof(char) * size);
	}
	out.close();
}

std::string GAME::get_date() const
{
	std::time_t t = std::time(0);   // get time now
	std::tm now;;
	localtime_s(&now, &t);
	std::string date;
	switch (now.tm_mon + 1)
	{
	case 1:
		date.append("Jan");
		break;
	case 2:
		date.append("Feb");
		break;
	case 3:
		date.append("Mar");
		break;
	case 4:
		date.append("Apr");
		break;
	case 5:
		date.append("May");
		break;
	case 6:
		date.append("Jun");
		break;
	case 7:
		date.append("Jul");
		break;
	case 8:
		date.append("Aug");
		break;
	case 9:
		date.append("Sep");
		break;
	case 10:
		date.append("Oct");
		break;
	case 11:
		date.append("Nov");
		break;
	case 12:
		date.append("Dec");
		break;
	default:
		break;
	}
	date.append(" " + std::to_string(now.tm_mday) + " " + std::to_string(now.tm_year + 1900));
	return date;
}

void GAME::onCreate()
{
	tetromino.onCreate();

	background_game.setSize(sf::Vector2f(window->getSize()));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);

	background_gameover.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	background_gameover.setPosition(window->getSize().x / 2 - background_gameover.getSize().x / 2, window->getSize().y / 2 - background_gameover.getSize().y / 2);

	txGameOver.setCharacterSize(window->getSize().y * 0.12f);
	txGameOver.setOrigin(txGameOver.getLocalBounds().left, txGameOver.getLocalBounds().top);
	txGameOver.setPosition(
		window->getSize().x / 2 - txGameOver.getGlobalBounds().width / 2,
		background_gameover.getPosition().y - txGameOver.getGlobalBounds().height / 2
	);

	txScore.setCharacterSize(window->getSize().y * 0.03f);
	txScore.setPosition(
		window->getSize().x / 2 - txScore.getGlobalBounds().width / 2 + 100,
		txb_Nick->getText().getPosition().y - txb_Nick->getText().getGlobalBounds().height / 2
	);

	txDate.setCharacterSize(window->getSize().y * 0.03f);
	txDate.setPosition(
		background_gameover.getPosition().x,
		background_gameover.getPosition().y + background_gameover.getSize().y - txDate.getGlobalBounds().height - 5
	);



}

void GAME::startUp()
{
	bPause = false;
	bGameOver = false;
	window->addOnCreate(this);

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER, -159, -143);
	b_Options->setTexture(AM->texture[AM_::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));


	b_Back = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 43);
	b_Back->setTexture(AM->texture[AM_::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));

	b_Exit = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER, -124, 143);
	b_Exit->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
	background_pause.setFillColor(sf::Color(55, 55, 55, 200));

	background_game.setSize(sf::Vector2f(window->getSize()));
	background_game.setTexture(&AM->texture[AM_::E_TEXTURE::T_BACKGROUND_GAME]);

	show_pause_menu(false);

	background_gameover.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	background_gameover.setPosition(window->getSize().x / 2 - background_gameover.getSize().x / 2, window->getSize().y / 2 - background_gameover.getSize().y / 2);
	background_gameover.setFillColor(sf::Color(30, 30, 30, 200));

	txb_Nick = window->GUI_.CreateTextBox(0,0, 350, 40, 1, "Enter your name");
	txb_Nick->setRelativePosition(gui::E_ANCHOR::A_CENTER, -450, -100);
	txb_Nick->setBoxStyle(1);
	txb_Nick->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	txb_Nick->setCharacterSize(25);
	txb_Nick->setFillColor(sf::Color::White);
	//txb_Nick->setActiveColor();

	b_Exit2 = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit2->setRelativePosition(
		gui::E_ANCHOR::A_TOP_LEFT,
		background_gameover.getPosition().x + background_gameover.getSize().x - 250, 
		background_gameover.getPosition().y + background_gameover.getSize().y - 90);
	b_Exit2->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit2->setHoveOverColor(sf::Color::White);
	b_Exit2->setFillColor(sf::Color(180, 180, 180));
	
	b_PlayAgain = window->GUI_.CreateButton(0, 0, 248, 86);
	b_PlayAgain->setRelativePosition(
		gui::E_ANCHOR::A_TOP_LEFT, 
		background_gameover.getPosition().x + background_gameover.getSize().x - 500, 
		background_gameover.getPosition().y + background_gameover.getSize().y - 90);
	b_PlayAgain->setTexture(AM->texture[AM_::E_TEXTURE::T_BPLAY]);
	b_PlayAgain->setHoveOverColor(sf::Color::White);
	b_PlayAgain->setFillColor(sf::Color(180, 180, 180));

	show_gameover_menu(false);

	txGameOver.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txGameOver.setString("Game Over");
	txGameOver.setCharacterSize(window->getSize().y * 0.12f);
	txGameOver.setFillColor(sf::Color(243, 208, 212));
	txGameOver.setOrigin(txGameOver.getLocalBounds().left, txGameOver.getLocalBounds().top);
	txGameOver.setPosition(
		window->getSize().x / 2 - txGameOver.getGlobalBounds().width / 2,
		background_gameover.getPosition().y - txGameOver.getGlobalBounds().height / 2
	);
	txGameOver.setOutlineColor(sf::Color::Black);
	txGameOver.setOutlineThickness(2);

	txScore.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txScore.setString(" your score :" + std::to_string(score));
	txScore.setCharacterSize(window->getSize().y * 0.03f);
	txScore.setFillColor(sf::Color(243, 208, 212));
	txScore.setPosition(
		window->getSize().x / 2 - txScore.getGlobalBounds().width / 2 + 100,
		txb_Nick->getText().getPosition().y - txb_Nick->getText().getGlobalBounds().height / 2
	);
	
	txDate.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txDate.setString(get_date());
	txDate.setCharacterSize(window->getSize().y * 0.03f);
	txDate.setFillColor(sf::Color(243, 208, 212));
	txDate.setPosition(
		background_gameover.getPosition().x,
		background_gameover.getPosition().y + background_gameover.getSize().y - txDate.getGlobalBounds().height - 5
	);

	set_standardmode();
	window->GUI_.clear();
}

ISTATE* GAME::standard_input(const sf::Event& event)
{
	ISTATE* state = this;
	
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
	{
		bPause = !bPause;
		show_pause_menu(bPause);
	}
	tetromino.handleInput(event);
	

	return state;
}

ISTATE* GAME::pause_input(const sf::Event& event)
{
	ISTATE* state = this;
	if (b_Back->Pressed() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
	{
		bPause = false;
		show_pause_menu(false);
		tetromino.pause();
	}
	else if (b_Options->Pressed())
	{
		state = &options;
	}
	else if (b_Exit->Pressed())
	{
		state = nullptr;
	}
	return state;
}

ISTATE* GAME::gameover_input(const sf::Event& event)
{
	ISTATE* state = this;
	if (b_PlayAgain->Pressed())
	{
		setToPlay();
		update_hightscore();
	}
	else if (b_Exit2->Pressed())
	{
		state = nullptr;
		show_gameover_menu(false);
		update_hightscore();
	}
	return state;
}

void GAME::standard_render() const
{
}

void GAME::pause_render() const
{
	window->draw(background_pause);
}

void GAME::gameover_render() const
{
	window->draw(background_gameover);
	window->draw(txGameOver);
	window->draw(txScore);
	window->draw(txDate);
}

void GAME::setToPlay()
{
	bGameOver = false;
	bPause = false;
	show_gameover_menu(false);
	tetromino.ini();
	set_standardmode();
}




