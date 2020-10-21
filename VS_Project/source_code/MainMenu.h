#pragma once
#include "Options.h"
#include "PDA.h"

namespace gui
{
    class Button;
}

class MAINMENU: public STATE
{
public:
    MAINMENU(class GameWindow*, class AM*);
    virtual ~MAINMENU();

    virtual STATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() const override ;

    virtual int manageInput(const sf::Event&) override { return 0; }
    virtual void show() override {};
    virtual void hide() override {};

private:
   OPTIONS options;
   PDA substates;

   gui::Button* b_NewGame;
   gui::Button* b_Options;
   gui::Button* b_Exit;
    

   void show_gui(bool show);
};




