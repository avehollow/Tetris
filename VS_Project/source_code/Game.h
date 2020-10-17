#pragma once

#include "FSM.h"
#include "Options.h"

namespace gui
{
    class Button;
};

class GAME: public STATE
{
    public:
        GAME(class GameWindow* w, class AM*);
        virtual STATE* handleInput(const sf::Event&) override;
        virtual void update(const float&) override;
        virtual void render() const override;
        
        virtual ~GAME();

    private:
        OPTIONS options;
        sf::Text menu[3];

        class AM* const AM_;
        class GameWindow* const window;

        gui::Button* b_Options;
        gui::Button* b_Back;

        enum SUBSTATE
        {
            NONE = 0,
            OPTIONS = 1
        }substate;
};

