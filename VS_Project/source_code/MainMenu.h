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
    gui::Button* b_HighScore;
    gui::Button* b_Back;

    sf::Text txHighScore;
    sf::Text date;
    sf::Text name;
    sf::Text score;

    sf::RectangleShape highScoreBg;
    bool bHighScore;
private:
    void show_gui(bool show);
    void show_high_score(bool show);
    void load_high_score();
    virtual void onCreate() override;
};



