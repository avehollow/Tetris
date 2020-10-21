#pragma once

#include "Options.h"

namespace gui
{
    class Button;
}

class PAUSE : public STATE
{
    friend class GAME;
public:
    PAUSE(class GameWindow*, class AM*);
    ~PAUSE();
    // Inherited via STATE
    virtual STATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() const override;
    virtual void show() override;
    virtual void hide() override;

    virtual int manageInput(const sf::Event&) override { return 0; }

private:
    OPTIONS options;
    sf::RectangleShape pause_background;

    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

   void show_gui(bool show);
};
