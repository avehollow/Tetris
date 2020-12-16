#pragma once
#include "STATE.h"
#include "WORLD.h"
#include "Settings.h"

namespace gui
{
	class Button;
	class DropDownList;
	class SliderList;
}


class OPTIONS: public ISTATE, public WORLD
{
public:
	OPTIONS();
	virtual ~OPTIONS();

	// Inherited via STATE
	virtual ISTATE* handleInput(const sf::Event&) override;
	virtual void update(const float&) override;
	virtual void render() const override;

	virtual void show() override;
	virtual void hide() override;
	virtual void startUp() override;

	const Settings::Movement* getMovementSettings() const;
private:
	virtual void onCreate() override;
	void show_gui(bool show);

	std::byte saveSettings() const;
	std::byte loadSettings();

	void fill_key_triggers();
	void set_text();
	void linkControlKeys();
	void linkABusing2lines(const sf::RectangleShape& A, const sf::RectangleShape& B, sf::Vertex* vertex, const sf::Color& color = sf::Color::White, int type = 0, float thickness = 2.0f);
	void erase_lines(sf::Vertex* vertex, std::size_t amount);

private:
	struct KeyTrigger
	{
		KeyTrigger(sf::RectangleShape r, short c)
		{
			rec = r;
			code = c;
		}
		sf::RectangleShape rec;
		short code;
	};

	struct ControlKey
	{
		ControlKey()
		{
			ptr = nullptr;
		}
		sf::Text text;
		KeyTrigger* ptr;
	};

private:
	std::vector<sf::VideoMode> vm;

	sf::Text tx_mv;
	sf::Text tx_sv;

	sf::Vertex lines[40];
	std::vector<KeyTrigger> k;
	ControlKey control_keys[5];


	Settings::Graphics gs;
	Settings::Movement ms;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;
	gui::SliderList* sl_music;
	gui::SliderList* sl_sound;

	sf::Sprite keyboard;

	float ppX;
	float ppY;

	int key_chosen;
	// z - szybkie
	// 3 strzalki - poruszanie
	// space - rotacja
};


inline const Settings::Movement* OPTIONS::getMovementSettings()const
{
	return &ms;
}
