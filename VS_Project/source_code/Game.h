#pragma once

#include "STATE.h"

#include "PDA.h"
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

        virtual STATE* handleInput(const sf::Event&) override;
        virtual void update(const float&) override;
        virtual void render() const override;


        virtual int manageInput(const sf::Event&) override { return 0; }
        virtual void show() override {};
        virtual void hide() override {};
        
    private:
        PAUSE pause;
        PDA substates;

};

