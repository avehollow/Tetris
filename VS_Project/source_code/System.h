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
	void Update(const long long& delta_time_ns);
	void Render();

private:
	sf::RenderWindow* window;
	sf::Event		  event;



	float uFrame = 0;
	float uFps   = 0;

	
	float rFrame = 0;
	float rFps   = 0;



	LARGE_INTEGER beg_time;
	LARGE_INTEGER end_time;
	LARGE_INTEGER elapsed;
	LARGE_INTEGER frequency;


	LARGE_INTEGER fps_time;



	sf::Font larabiefontRG;
	sf::Text r_fps;
	sf::Text u_fps;

	int FPS;
};

