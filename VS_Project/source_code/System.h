#pragma once

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
	sf::RenderWindow* window;
	sf::Event		  event;

	float uFrame = 0;
	float uFps   = 0;

	float rFrame = 0;
	float rFps   = 0;

	sf::Font larabiefontRG;
	sf::Text r_fps;
	sf::Text u_fps;

	int FPS;
};

