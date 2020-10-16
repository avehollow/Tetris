#include "pch.h"
#include "System.h"



//! 1s = 1'000'000'000 ns
//! 1s = 1'000'000 us
//! 1s = 1'000 ms

#define _1s_ 1'000'000ll
#define _0s_ 0ll

#define FS1

System::System()
#ifdef FS
	: window_(sf::VideoMode::getDesktopMode(), "Tetris", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen)
	, GUI_(&window_)
#else
	: window_(sf::VideoMode(1280, 720, 32), "Tetris", sf::Style::Titlebar | sf::Style::Close)
	, GUI_(&window_)
#endif // FS
{

	FPS = 120;
	
	r_fps.setPosition(window_.getSize().x * 0.85, window_.getSize().y * 0);
	u_fps.setPosition(window_.getSize().x * 0.85, window_.getSize().y * 0.05);
	r_fps.setFont(AM_.font[AM::E_FONT::F_LARABIEFONTRG]);
	u_fps.setFont(AM_.font[AM::E_FONT::F_LARABIEFONTRG]);
	r_fps.setCharacterSize(30);
	u_fps.setCharacterSize(30);
	r_fps.setFillColor(sf::Color(255, 255, 255, 70));
	u_fps.setFillColor(sf::Color(255, 255, 255, 70));

	// AVE LOOK not necessary for <60 fps
	timeBeginPeriod(1);
}

System::~System()
{
	// AVE LOOK not necessary for <60 fps
	timeEndPeriod(1);
}


void System::UpdateEvents()
{
	
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
			break;
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window_.close();
			break;
		}

		GUI_.handleEvent(event);
	}
}

void System::Update(const long long& teta_time)
{
	float dt = teta_time / (float)_1s_;
}

void System::Render()
{
	GUI_.draw();

	window_.draw(r_fps);
	window_.draw(u_fps);

	window_.display();
	window_.clear();
}



void System::Run()
{	
	const long long TIME_PER_FRAME = (_1s_ / FPS);

	// Time Since Last Update
	long long TSLU = 0;

	// Frame Time
	LARGE_INTEGER FT		= {0};
	LARGE_INTEGER beg_time	= {0};
	LARGE_INTEGER end_time	= {0};
	LARGE_INTEGER frequency = {0};
	LARGE_INTEGER fps_time	= {0};

	// AVE DELETE debug
	LARGE_INTEGER t1	= {0};
	LARGE_INTEGER t2	= {0};

	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&beg_time);
	// // // //
	while (window_.isOpen())
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
		{
			// AVE DELETE debug
			//QueryPerformanceCounter(&t1);
			std::this_thread::sleep_for(std::chrono::microseconds(FT.QuadPart));
			//QueryPerformanceCounter(&t2);
			//std::cout << FT.QuadPart - (((t2.QuadPart - t1.QuadPart) * _1s_) / frequency.QuadPart) << '\n';
		}
	
	} // Game Loop
}
