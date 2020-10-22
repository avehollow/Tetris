#pragma once
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
	virtual E_STATE handleInput(const sf::Event&) override;
	virtual void update(const float&) override;
	virtual void render() const override;

	virtual void show() override;
	virtual void hide() override;
	virtual void onCreate() override;

private:
	std::vector<sf::VideoMode> vm;

	GraphicsSettings gs;
	MovementSettings ms;

	gui::Button* b_Applay;
	gui::Button* b_Back;
	gui::DropDownList* ddl_vm;

	void show_gui(bool show);
};


