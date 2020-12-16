#include "pch.h"
#include "MainMenu.h"
#include "GUI/Button.h"
#include "Options.h"
#include "Game.h"

MAINMENU main_menu;
extern GAME game;
extern OPTIONS options;

MAINMENU::MAINMENU()
{
	
}

ISTATE* MAINMENU::handleInput(const sf::Event& event)
{
	ISTATE* state = this;
	if (bHighScore)
	{
		if (b_Back->Pressed())
		{	
			show_high_score(bHighScore = false);
		}
	}
	else if (b_NewGame->Pressed())
	{
		AM->sound[AM_::E_SOUND::S_CLICK_1].play();
		state = &game;
		game.setToPlay();;
	}
	else if (b_Exit->Pressed())
	{
		window->close();
	}
	else if (b_Options->Pressed())
	{
		state = &options;
	}
	else if (b_HighScore->Pressed())
	{
		show_high_score(bHighScore = true);
		load_high_score();
	}

    return state;
}

void MAINMENU::update(const float& d)
{

}

void MAINMENU::render()const
{
	if (bHighScore)
	{
		window->draw(highScoreBg);
		window->draw(txHighScore);
		window->draw(date);
		window->draw(name);
		window->draw(score);
		window->draw(pos);
	}
	
}

void MAINMENU::show()
{
	show_gui(true);
}

void MAINMENU::hide()
{
	show_gui(false);
}

void MAINMENU::onCreate()
{
	highScoreBg.setSize(sf::Vector2f(window->getSize().x, window->getSize().y / 2));
	highScoreBg.setPosition(0, window->getSize().y / 2 - highScoreBg.getSize().y / 2);

	txHighScore.setCharacterSize(window->getSize().y * 0.10f);
	txHighScore.setPosition(window->getSize().x / 2 - txHighScore.getGlobalBounds().width / 2, highScoreBg.getPosition().y - txHighScore.getGlobalBounds().height / 2);
	txHighScore.setOrigin(txHighScore.getLocalBounds().left, txHighScore.getLocalBounds().top);

	pos.setCharacterSize(window->getSize().y * 0.03f);
	pos.setOrigin(pos.getLocalBounds().left, pos.getLocalBounds().top);
	pos.setPosition(window->getSize().x * 0.02f, window->getSize().y / 2 - pos.getGlobalBounds().height / 2);

	date.setCharacterSize(window->getSize().y * 0.03f);
	date.setOrigin(date.getLocalBounds().left, date.getLocalBounds().top);
	date.setPosition(window->getSize().x * 0.08f, window->getSize().y / 2 - date.getGlobalBounds().height / 2);

	name.setCharacterSize(window->getSize().y * 0.03f);
	name.setOrigin(name.getLocalBounds().left, name.getLocalBounds().top);
	name.setPosition(window->getSize().x * 0.30f, window->getSize().y / 2 - name.getGlobalBounds().height / 2);
	
	score.setCharacterSize(window->getSize().y * 0.03f);
	score.setOrigin(score.getLocalBounds().left, score.getLocalBounds().top);
	score.setPosition(window->getSize().x * 0.55f, window->getSize().y / 2 - score.getGlobalBounds().height / 2);
	
}
void MAINMENU::startUp()
{
	window->addOnCreate(this);
	// AVE LOOK options must be before game.startUp(); because options must load graphics and motion settings first
	options.startUp();

	game.startUp();
	
	b_Exit = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Exit->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_Exit->getSize().x / 2, 126);
	b_Exit->setTexture(AM->texture[AM_::E_TEXTURE::T_BEXIT]);
	b_Exit->setHoveOverColor(sf::Color::White);
	b_Exit->setFillColor(sf::Color(180, 180, 180));

	b_Options = window->GUI_.CreateButton(0, 0, 318, 86);
	b_Options->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_Options->getSize().x / 2, 234);
	b_Options->setTexture(AM->texture[AM_::E_TEXTURE::T_BOPTIONS]);
	b_Options->setHoveOverColor(sf::Color::White);
	b_Options->setFillColor(sf::Color(180, 180, 180));

	b_NewGame = window->GUI_.CreateButton(0, 0, 318, 86);
	b_NewGame->setRelativePosition(gui::E_ANCHOR::A_CENTER_BOTTOM, -b_NewGame->getSize().x / 2, 340);
	b_NewGame->setTexture(AM->texture[AM_::E_TEXTURE::T_BNEWGAME]);
	b_NewGame->setHoveOverColor(sf::Color::White);
	b_NewGame->setFillColor(sf::Color(180, 180, 180));


	highScoreBg.setSize(sf::Vector2f(window->getSize().x,window->getSize().y / 2 ));
	highScoreBg.setFillColor(sf::Color(30, 30, 30, 200));
	highScoreBg.setPosition(0, window->getSize().y / 2 - highScoreBg.getSize().y / 2);

	b_HighScore = window->GUI_.CreateButton(0, 0, 400, 87);
	b_HighScore->setRelativePosition(gui::E_ANCHOR::A_BOTTOM_LEFT, 10, 126);
	b_HighScore->setTexture(AM->texture[AM_::E_TEXTURE::T_BHIGHSCORE]);
	b_HighScore->setHoveOverColor(sf::Color::White);
	b_HighScore->setFillColor(sf::Color(180, 180, 180));
	
	b_Back = window->GUI_.CreateButton(0, 0, 247, 86);
	b_Back->setRelativePosition(gui::E_ANCHOR::A_TOP_RIGHT, 250, highScoreBg.getPosition().y + highScoreBg.getSize().y - 90);
	b_Back->setTexture(AM->texture[AM_::E_TEXTURE::T_BBACK]);
	b_Back->setHoveOverColor(sf::Color::White);
	b_Back->setFillColor(sf::Color(180, 180, 180));
	window->GUI_.erase(b_Back);

	txHighScore.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	txHighScore.setString("HightScore");
	txHighScore.setFillColor(sf::Color(178, 34, 34, 255));
	txHighScore.setCharacterSize(window->getSize().y * 0.10f);
	txHighScore.setOrigin(txHighScore.getLocalBounds().left, txHighScore.getLocalBounds().top);
	txHighScore.setPosition(window->getSize().x / 2 - txHighScore.getGlobalBounds().width / 2, highScoreBg.getPosition().y - txHighScore.getGlobalBounds().height / 2);
	
	pos.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	pos.setString("");
	pos.setFillColor(sf::Color(178, 34, 34, 255));
	pos.setCharacterSize(window->getSize().y * 0.03f);
	pos.setOrigin(pos.getLocalBounds().left, pos.getLocalBounds().top);
	pos.setPosition(window->getSize().x * 0.02f, date.getPosition().y);

	date.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	date.setString("");
	date.setCharacterSize(window->getSize().y * 0.03f);
	date.setOrigin(date.getLocalBounds().left, date.getLocalBounds().top);
	date.setPosition(window->getSize().x * 0.08f, highScoreBg.getPosition().y + txHighScore.getGlobalBounds().height / 2);
	

	name.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	name.setString("");
	name.setFillColor(sf::Color(178, 34, 34, 255));
	name.setCharacterSize(window->getSize().y * 0.03f);
	name.setOrigin(name.getLocalBounds().left, name.getLocalBounds().top);
	name.setPosition(window->getSize().x * 0.30f, date.getPosition().y);

	score.setFont(AM->font[AM_::E_FONT::F_NINEPIN]);
	score.setString("");
	score.setCharacterSize(window->getSize().y * 0.03f);
	score.setOrigin(score.getLocalBounds().left, score.getLocalBounds().top);
	score.setPosition(window->getSize().x * 0.55f, date.getPosition().y);	
	
	
	
	bHighScore = false;
	window->GUI_.clear();
	show_gui(true);
}

MAINMENU::~MAINMENU()
{
	//puts("Destruktor ~MAINMENU");
}


void MAINMENU::show_gui(bool show)
{
	if (show)
	{
		while (ShowCursor(TRUE) < 0);
		window->GUI_.add(b_NewGame);
		window->GUI_.add(b_Options);
		window->GUI_.add(b_Exit);
		window->GUI_.add(b_HighScore);
	}
	else
	{
		while (ShowCursor(FALSE) >= 0);
		window->GUI_.erase(b_NewGame);
		window->GUI_.erase(b_Options);
		window->GUI_.erase(b_Exit);
		window->GUI_.erase(b_HighScore);
	}

}

void MAINMENU::show_high_score(bool show)
{
	show_gui(!show);

	if (show)
	{
		while (ShowCursor(TRUE) < 0);
		window->GUI_.add(b_Back);
	}
	else
	{
		window->GUI_.erase(b_Back);
	}
	
	
}

void MAINMENU::load_high_score()
{
	std::fstream out;
	std::vector<std::tuple<std::array<char, 20>, int, std::array<char, 20>>> h;
	h.resize(11);

	out.open("x@Ew.java", std::ios::binary | std::ios::in);
	if (!out.is_open())
		return;
	
	std::string n("");
	std::string s("");
	std::string d("");
	std::string p("");
	for (size_t i = 0; i < 10; i++)
	{
		int size = 0;
		out.read((char*)&size, sizeof(int));
		out.read((char*)std::get<0>(h[i]).data(), sizeof(char) * size);
																		n.append(std::get<0>(h[i]).data());
													
		out.read((char*)&std::get<1>(h[i]), sizeof(int));
																		s.append(std::to_string(int(std::get<1>(h[i]))));
																	
		out.read((char*)&size, sizeof size);
		out.read((char*)std::get<2>(h[i]).data(), sizeof(char) * size);
																		p.append(std::to_string(i+1) + ".\n");
																		d.append(std::get<2>(h[i]).data());
																		n.append("\n");
																		s.append("\n");
																		d.append("\n");
	}
	name.setString(n);
	score.setString(s);
	date.setString(d);
	pos.setString(p);

	pos.setPosition(window->getSize().x * 0.02f, window->getSize().y / 2 - pos.getGlobalBounds().height / 2);
	date.setPosition(window->getSize().x * 0.08f, window->getSize().y / 2 - date.getGlobalBounds().height / 2);
	name.setPosition(window->getSize().x * 0.25f, window->getSize().y / 2 - name.getGlobalBounds().height / 2);
	score.setPosition(window->getSize().x * 0.50f, window->getSize().y / 2 - score.getGlobalBounds().height / 2);
}
