#pragma once
#include "STATE.h"
#include "WORLD.h"

namespace gui
{
    class Button;
}

class MAINMENU : public ISTATE, public WORLD
{
public:
    MAINMENU();
    virtual ~MAINMENU();

    virtual ISTATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() const override;

    virtual void show() override;
    virtual void hide() override;
    virtual void startUp() override;

private:
    gui::Button* b_NewGame;
    gui::Button* b_Options;
    gui::Button* b_Exit;


    void show_gui(bool show);
    virtual void onCreate() override;
};



