#include "pch.h"
#include "assetmanager.h"



AM_::AM_()
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

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/background_game.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/green.png");	

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/blue.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/gold.png");	
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/red.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/cyan.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/purple.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/yellow.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/place_holder.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/bhighscore.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/fire1.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/poof.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/conffeti.png");

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/fireworks.png");
	
	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/error.png");	

	texture.emplace_back(sf::Texture());
	texture.back().loadFromFile("data/texture/keyboard.png");
}

AM_::~AM_()
{
}
