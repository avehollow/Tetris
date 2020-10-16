#pragma once

#include "assetmanager.h"
#include "GameWindow.h"
#include "FSM.h"

class System
{
public:
	System();
	~System();

public:
	void Run();

private:
	void UpdateEvents();
	void Update(const long long& teta_time);
	void Render();

private:
	GameWindow  window_;
	sf::Text r_fps;
	sf::Text u_fps;
	AM AM_;
	sf::Event event_;
	FSM menu_;

	float uFrame = 0;
	float uFps   = 0;

	float rFrame = 0;
	float rFps   = 0;
	
	int FPS;
};

