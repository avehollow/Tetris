#pragma once


__interface ISTATE // same as  class __declspec(novtable) ISTATE { ... };
{
	ISTATE* handleInput(const sf::Event&);
	void update(const float&);
	void render();
	void show();
	void hide();
	void onCreate();
	void startUp();
};