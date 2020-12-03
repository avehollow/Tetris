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
	std::vector<sf::VideoMode> vm;

	GraphicsSettings gs;
	MovementSettings ms;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;
	gui::SliderList* sl_music;

	void show_gui(bool show);
	virtual void onCreate() override;
};


