#include "pch.h"
#include "System.h"



//! 1s = 1'000'000'000 ns
//! 1s = 1'000'000 us
//! 1s = 1'000 ms

#define _1s_ 1'000'000
#define _0s_ 0


System::System()
{
	window = new sf::RenderWindow(
		sf::VideoMode(1280, 720, 32), " ", sf::Style::Titlebar | sf::Style::Close
	);

	FPS = 120;
	
	larabiefontRG.loadFromFile("data/fonts/larabiefontRG.ttf");
	r_fps.setPosition(window->getSize().x * 0.85, window->getSize().y * 0);
	u_fps.setPosition(window->getSize().x * 0.85, window->getSize().y * 0.05);
	r_fps.setFont(larabiefontRG);
	u_fps.setFont(larabiefontRG);
	r_fps.setCharacterSize(30);
	u_fps.setCharacterSize(30);
	r_fps.setFillColor(sf::Color(255, 255, 255, 70));
	u_fps.setFillColor(sf::Color(255, 255, 255, 70));
	
	fps_time.QuadPart = 0;
}

System::~System()
{
	delete window;
}


void System::UpdateEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
			window->close();
	}
}

void System::Update(const long long& delta_time_ns)
{
	float dt = delta_time_ns / 10'000.0f;

}

void System::Render()
{
	window->draw(r_fps);
	window->draw(u_fps);

	window->display();
	window->clear();
}



void System::Run()
{	
	// Frame Time
	LARGE_INTEGER FT;

	const long long TIME_PER_FRAME = (_1s_ / (long long)FPS);
	// Time Since Last Update
	long long TSLU = 0;


	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&beg_time);
	while (window->isOpen())
	{
		QueryPerformanceCounter(&end_time);
		TSLU += (((end_time.QuadPart - beg_time.QuadPart) * _1s_) / frequency.QuadPart);
		fps_time.QuadPart += (((end_time.QuadPart - beg_time.QuadPart) * _1s_) / frequency.QuadPart);
		QueryPerformanceCounter(&beg_time);

		rFrame++;
		if (fps_time.QuadPart >= _1s_)
		{
			uFps = uFrame / (fps_time.QuadPart / _1s_);
			rFps = rFrame / (fps_time.QuadPart / _1s_);
			rFrame = 0;
			uFrame = 0;
			fps_time.QuadPart -= _1s_;
		}

		u_fps.setString(sf::String("UFPS: " + std::to_string((int)uFps)));
		r_fps.setString(sf::String("RFPS: " + std::to_string((int)rFps)));



		this->UpdateEvents();
		while (TSLU >= TIME_PER_FRAME)
		{
			++uFrame;
			this->Update(TIME_PER_FRAME);
			TSLU -= TIME_PER_FRAME;
		}
		this->Render();

		
		QueryPerformanceCounter(&FT);
		FT.QuadPart = (FT.QuadPart - end_time.QuadPart);
		FT.QuadPart *= _1s_;
		FT.QuadPart /= frequency.QuadPart;

		FT.QuadPart = (TIME_PER_FRAME - FT.QuadPart);
		FT.QuadPart -= TSLU;

		if (FT.QuadPart > _0s_)
			std::this_thread::sleep_for(std::chrono::microseconds(FT.QuadPart));
	}
}
