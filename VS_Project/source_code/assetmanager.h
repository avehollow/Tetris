#pragma once

class AM
{
public:
	AM();
	~AM();

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
};

