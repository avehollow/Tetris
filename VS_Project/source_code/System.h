#pragma once

#include "assetmanager.h"
#include "GameWindow.h"
#include "PDA.h"
#include "WORLD.h"
#include "STATE.h"

class System: public WORLD
{
public:
	System();
	~System();

public:
	void Run();

private:
	void HandleInput();
	void Update(const long long& teta_time);
	void Render();

private:
	sf::Text r_fps;
	sf::Text u_fps;
	sf::Event event_;
	PDA<STATE> menu_;

	float uFrame = 0;
	float uFps   = 0;

	float rFrame = 0;
	float rFps   = 0;
	
	int FPS;
};

