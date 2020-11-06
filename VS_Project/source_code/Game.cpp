#include "pch.h"
#include "Game.h"
#include "Button.h"
#include "TextBox.h"
#include "Options.h"
#include <span>
GAME game;

extern OPTIONS options;

ISTATE* GAME::handleInput(const sf::Event& event)
{
	ISTATE* state = this;
	
	if (bPause)
	{
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
			//bPause = false;
		}
	}
	else if (bGameOver)
	{
		if (b_PlayAgain->Pressed())
		{
			tetromino.ini();
			show_gameover_menu(false);
		}
		if (b_Exit2->Pressed())
		{
			state = nullptr;
			show_gameover_menu(false);
		}
	}
	else
	{
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			bPause = !bPause;
			show_pause_menu(bPause);
		}
		tetromino.handleInput(event);
	}
		
	
	return state;
}


void GAME::update(const float& tt)
{
	if (!bPause)
	{
		bGameOver = score = tetromino.update(tt);
		if (bGameOver)
			show_gameover_menu(true);
		
	}
	else
	{
		tetromino.pause();
	}

}

void GAME::render()const
{
	window->draw(background_game);

	tetromino.draw(window);

	if (bPause)
	{
		window->draw(background_pause);
	}
	else if (bGameOver)
	{
		window->draw(background_gameover);
		window->draw(txGameOver);
		window->draw(txScore);
		window->draw(txDate);
	}
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
	b_Back->visible(show);
	b_Options->visible(show);
	b_Exit->visible(show);
}

void GAME::show_gameover_menu(bool show)
{
	b_Exit2->visible(show);
	b_PlayAgain->visible(show);
	txb_Nick->visible(show);
	txScore.setString(" your score :" + std::to_string(score));
}

void GAME::update_hightscore()
{
	std::fstream out;
	std::vector<std::tuple<std::array<char, 20>, int, std::array<char, 20>>> h;
	h.resize(11);

	out.open("x@Ew.java", std::ios::binary | std::ios::in);

	for (size_t i = 0; i < 10; i++)
	{
		int size = 0;
		out.read((char*)&size, sizeof(int));
		out.read((char*)std::get<0>(h[i]).data(), sizeof(char) * size);
		out.read((char*)&std::get<1>(h[i]), sizeof(int));
		out.read((char*)&size, sizeof size);
		out.read((char*)std::get<2>(h[i]).data(), sizeof(char) * size);
	}

	std::string nick = txb_Nick->getString();
	for (size_t i = 0, int size = nick.size(); i < size && i < 20; i++)
	{
		std::get<0>(h[10])[i] = nick[i];
	}
	std::span<const char, 20> date{ txDate.getString().toAnsiString()};
	int i = 0;
	for (auto& tx : date)
	{
		std::get<2>(h[11])[i++] = tx;
		// work?
	}
	std::sort(
		h.begin(),
		h.end(),
		[](
			auto const& lhs,
			auto const& rhs)
		{ return std::get<1>(lhs) > std::get<1>(rhs); }
	);


	out.close();


	out.open("x@Ew.java", std::ios::binary | std::ios::out);





	for (size_t i = 0; i < 10; i++)
	{
		int size = names[i].size();
		out.write((const char*)&size, sizeof(int));
		out.write(names[i].data(), sizeof(char) * names[i].size());
		out.write((const char*)&score[i], sizeof(int));
		size = sizeof(__DATE__);
		out.write((char*)&size, sizeof size);
		out.write(__DATE__, sizeof(__DATE__));
	}
	out.close();
	for (size_t i = 0; i < 10; i++)
	{
		printf("%15s %-20s %5d %15s \n", " ", names[i].data(), score[i], __DATE__);
	}


	



}



void GAME::onCreate()
{
	tetromino.onCreate();

	background_game.setSize(sf::Vector2f(window->getSize()));

	background_pause.setSize(sf::Vector2f(window->getSize().x / 3, window->getSize().y));
	background_pause.setPosition(window->getSize().x / 2 - background_pause.getSize().x / 2, window->getSize().y / 2 - background_pause.getSize().y / 2);
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

	txb_Nick = window->GUI_.CreateTextBox(0,0, 200, 40, 1, "Enter your name");
	txb_Nick->setRelativePosition(gui::E_ANCHOR::A_CENTER, -450, -100);
	txb_Nick->setBoxStyle(1);
	txb_Nick->setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	txb_Nick->setCharacterSize(25);
	txb_Nick->setFillColor(sf::Color::White);
	//txb_Nick->setActiveColor();

	b_Exit2 = window->GUI_.CreateButton(0, 0, 248, 86);
	b_Exit2->setRelativePosition(gui::E_ANCHOR::A_CENTER, 220, 180);
	b_Exit2->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit2->setHoveOverColor(sf::Color::White);
	b_Exit2->setFillColor(sf::Color(180, 180, 180));
	
	b_PlayAgain = window->GUI_.CreateButton(0, 0, 248, 86);
	b_PlayAgain->setRelativePosition(gui::E_ANCHOR::A_CENTER, -70, 180);
	b_PlayAgain->setTexture(AM->texture[AM_::E_TEXTURE::T_BPLAY]);
	b_PlayAgain->setHoveOverColor(sf::Color::White);
	b_PlayAgain->setFillColor(sf::Color(180, 180, 180));

	show_gameover_menu(false);

	txGameOver.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txGameOver.setString("Game Over");
	txGameOver.setCharacterSize(120);
	txGameOver.setFillColor(sf::Color(243, 208, 212));
	txGameOver.setPosition(
		window->getSize().x / 2 - txGameOver.getGlobalBounds().width / 2,
		background_gameover.getPosition().y - txGameOver.getGlobalBounds().height / 2
	);
	txGameOver.setOutlineColor(sf::Color::Black);
	txGameOver.setOutlineThickness(2);

	txScore.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txScore.setString(" your score :" + std::to_string(score));
	txScore.setCharacterSize(30);
	txScore.setFillColor(sf::Color(243, 208, 212));
	txScore.setPosition(
		window->getSize().x / 2 - txScore.getGlobalBounds().width / 2,
		window->getSize().y / 2 - 100 
	);
	
	txDate.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txDate.setString((__DATE__));
	txDate.setCharacterSize(30);
	txDate.setFillColor(sf::Color(243, 208, 212));
	txDate.setPosition(
		background_gameover.getPosition().x,
		background_gameover.getPosition().y + background_gameover.getSize().y - txDate.getGlobalBounds().height - 5
	);
}

void GAME::setToPlay()
{
	bGameOver = false;
	bPause = false;
	tetromino.ini();
}




