#pragma once

#include "FSM.h"
#include "Options.h"

namespace gui
{
    class Button;
}

class MAINMENU: public STATE
{
public:
    MAINMENU(sf::RenderWindow*, class AM*);
    virtual STATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() const override ;

    virtual ~MAINMENU();

private:
    OPTIONS options;

    class GameWindow* const window;
    
    class AM* const AM_;
 
   gui::Button* b_NewGame;
   gui::Button* b_Options;
   gui::Button* b_Exit;
    
    enum SUBSTATE
    {
        NONE = 0,
        OPTIONS = 1
    } substate;
};

