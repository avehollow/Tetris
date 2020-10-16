#pragma once

#include "assetmanager.h"
#include "GUI.h"

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
	sf::RenderWindow  window_;
	sf::Text r_fps;
	sf::Text u_fps;
	AM AM_;
	sf::Event		  event;
	gui::GUI GUI_;

	float uFrame = 0;
	float uFps   = 0;

	float rFrame = 0;
	float rFps   = 0;
	
	int FPS;
};

