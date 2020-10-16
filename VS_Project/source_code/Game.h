#pragma once

#include "FSM.h"
#include "Options.h"
class GAME: public STATE
{
    public:
        GAME(sf::RenderWindow*, class AM*);
        virtual STATE* handleInput(const sf::Event&) override;
        virtual void update(const float&) override;
        virtual void render() const override;
        
        virtual ~GAME();

    private:
        sf::RenderWindow* const window;
        sf::Text menu[3];

        OPTIONS options;

        class AM* const AM_;

        enum SUBSTATE
        {
            NONE = 0,
            OPTIONS = 1
        };
        SUBSTATE substate;

        enum MENUTX
        {
            M_MAINMENU = 0,
            M_OPTIONS = 1,
            M_EXIT = 2
        };
};

