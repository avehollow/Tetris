#include "pch.h"
#include "assetmanager.h"



AM::AM()
{
	///
	//! FONTS
	///
	font.emplace_back(sf::Font());
	font.back().loadFromFile("data/font/larabiefontRG.ttf");

	font.emplace_back(sf::Font());
	font.back().loadFromFile("data/font/ninepin.ttf");


	///
	//! SOUND_BUFFER
	///
	sound_buffer.emplace_back(sf::SoundBuffer());
	sound_buffer.back().loadFromFile("data/sound/click1.ogg");

	sound_buffer.emplace_back(sf::SoundBuffer());
	sound_buffer.back().loadFromFile("data/sound/click2.ogg");

	///
	//! SOUND
	///
	sound.emplace_back(sf::Sound());
	sound.back().setBuffer(sound_buffer[0]);

	sound.emplace_back(sf::Sound());
	sound.back().setBuffer(sound_buffer[1]);

	///
	//! TEXTURE
	///
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bapply.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bexit.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bsphere.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bnewgame.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/boptions.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bback.png");


	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bplay.png");
}

AM::~AM()
{
}
