#pragma once


__interface ISTATE // to samo co   class __declspec(novtable) ISTATE { ... };
{
	ISTATE* handleInput(const sf::Event&);
	void update(const float&);
	void render() const;
	void show();
	void hide();
	void onCreate();
	void startUp();
};