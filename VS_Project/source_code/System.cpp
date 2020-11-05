#include "pch.h"
#include "System.h"
#include "MainMenu.h"

//! 1s = 1'000'000'000 ns
//! 1s = 1'000'000 us
//! 1s = 1'000 ms

#define _1s_ 1'000'000ll
#define _0s_ 0ll



extern MAINMENU main_menu;

System::System()
	: menu_(&main_menu)
{
	WORLD::ini();
	wnd = window;
	//wnd->GUI_.reserve(50);
	main_menu.startUp();

	std::srand(time(NULL));

	FPS = 120;
	
	r_fps.setPosition(wnd->getSize().x * 0.90f, wnd->getSize().y * 0.0f);
	u_fps.setPosition(wnd->getSize().x * 0.90f, wnd->getSize().y * 0.025f);
	r_fps.setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	u_fps.setFont(AM->font[AM_::E_FONT::F_LARABIEFONTRG]);
	r_fps.setCharacterSize(20);
	u_fps.setCharacterSize(20);
	r_fps.setFillColor(sf::Color(255, 255, 255, 70));
	u_fps.setFillColor(sf::Color(255, 255, 255, 70));

	// AVE LOOK not necessary for <60 fps
	timeBeginPeriod(1);
}

System::~System()
{
	WORLD::free();
	// AVE LOOK not necessary for <60 fps
	timeEndPeriod(1);
}


void System::HandleInput()
{
	
	while (wnd->pollEvent(event_))
	{
		if (event_.type == sf::Event::Closed)
		{
			wnd->close();
			break;
		}

		wnd->GUI_.handleEvent(event_);
		menu_.handleInput(event_);
	}
}

void System::Update(const long long& teta_time)
{
	float tt = teta_time / (float)_1s_;
	menu_.update(tt);
}

void System::Render()
{
	menu_.render();



	wnd->GUI_.draw();

	wnd->draw(r_fps);
	wnd->draw(u_fps);

	wnd->display();
	wnd->clear();
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
	while (wnd->isOpen())
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


		this->HandleInput();
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
