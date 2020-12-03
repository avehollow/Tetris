#pragma once

class AM_
{
public:
	AM_();
	~AM_();

	std::vector<sf::Font>    font;
	std::vector<sf::Texture> texture;
	std::vector<sf::Sound>   sound;
	std::vector<sf::Music>   music;

private:
	std::vector<sf::SoundBuffer> sound_buffer;

public:
	enum E_FONT
	{
		F_LARABIEFONTRG = 0,
		F_NINEPIN = 1
	};

	enum E_SOUND
	{
		S_CLICK_1 = 0,
		S_CLICK_2 = 1,
	};

	enum E_TEXTURE
	{
		T_BAPPLAY = 0,
		T_BEXIT = 1,
		T_BSPHERE,
		T_BNEWGAME,
		T_BOPTIONS,
		T_BBACK,
		T_BPLAY,
		T_BACKGROUND_GAME,
		T_CUBE_GREEN,
		T_CUBE_BLUE,
		T_CUBE_GOLD,
		T_CUBE_RED,
		T_CUBE_CYAN,
		T_CUBE_PURPLE,
		T_CUBE_YELLOW,
		T_CUBE_PLACEHOLDER,
		T_BHIGHSCORE,
		T_FIRE1,
		T_POOF,
		T_CONFFETI,
		T_FIREWORKS,
		T_ERROR
	};
};

