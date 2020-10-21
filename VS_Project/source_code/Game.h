#pragma once

#include "STATE.h"
#include "PAUSE.h"

namespace gui
{
    class Button;
};

class GAME: public STATE
{
    public:
        GAME(class GameWindow* w, class AM*);
        virtual ~GAME();

        virtual E_STATE handleInput(const sf::Event&) override;
        virtual void update(const float&) override;
        virtual void render() const override;


        virtual void show() override;
        virtual void hide() override;

private:
    sf::RectangleShape pause_background;

    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

    void show_gui(bool show);
    bool isPause;
};

