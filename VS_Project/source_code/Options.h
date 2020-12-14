#pragma once
#include "STATE.h"
#include "WORLD.h"

namespace gui
{
	class Button;
	class DropDownList;
	class SliderList;
}

struct GraphicsSettings
{

};
struct MovementSettings
{
	int control_keys[5];
};

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

private:
	virtual void onCreate() override;
	void show_gui(bool show);

	void fill_key_triggers();
	void set_text();
	void draw_lines(const sf::RectangleShape& start, const sf::RectangleShape& end, sf::Vertex* vertex, const sf::Color& color = sf::Color::White, int type = 0, float thickness = 2.0f);
	void erase_lines(sf::Vertex* vertex, std::size_t amount);

private:
	std::vector<sf::VideoMode> vm;
	GraphicsSettings gs;
	MovementSettings ms;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;
	gui::SliderList* sl_music;

	sf::Sprite keyboard;

	float ppX;
	float ppY;

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

	std::vector<KeyTrigger> k;

	struct ControlKey
	{
		ControlKey()
		{
			ptr = nullptr;
		}
		sf::Text text;
		KeyTrigger* ptr;
	};
	ControlKey control_keys[6];

	sf::Vertex lines[40];

	sf::Text* ctx;
	sf::RectangleShape* crs;
	int key_chosen;
	// z - szybkie
	// 3 strzalki - poruszanie
	// space - rotacja
};


