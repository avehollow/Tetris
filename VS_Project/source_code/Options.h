#pragma once
#include "SYMBOLS.H"

#include "STATE.h"
namespace gui
{
	class Button;
	class DropDownList;
}

struct GraphicsSettings
{

};

struct MovementSettings
{

};


class OPTIONS: public STATE
{
public:
	OPTIONS(class GameWindow* w, class AM*);
	virtual ~OPTIONS();

	// Inherited via STATE
	virtual STATE* handleInput(const sf::Event&) override;
	virtual int manageInput(const sf::Event&) override;
	virtual void update(const float&) override;
	virtual void render() const override;
	virtual void show() override;
	virtual void hide() override;


private:
	GraphicsSettings gs;
	MovementSettings ms;

	class AM* const AM_;
	class GameWindow* const window;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;



	void show_gui(bool show);
};

