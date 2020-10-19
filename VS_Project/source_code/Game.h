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
        virtual ~GAME();

        virtual STATE* handleInput(const sf::Event&) override;
        virtual void update(const float&) override;
        virtual void render() const override;


        virtual int manageInput(const sf::Event&) override { return 0; }
        virtual void show() override {};
        virtual void hide() override {};
        
    private:
        OPTIONS options;
        std::stack<STATE*> substate;
        sf::RectangleShape pause_background;

        class AM* const AM_;
        class GameWindow* const window;

        gui::Button* b_Options;
        gui::Button* b_Back;
        gui::Button* b_Exit;


        void show_gui(bool show);
};

