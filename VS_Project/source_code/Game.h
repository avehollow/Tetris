#pragma once

#include "STATE.h"
#include "Tetromino.h"

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
    virtual void onCreate() override;
    void ini();
private:
    Tetromino tetromino;

    sf::RectangleShape background_pause;
    sf::RectangleShape background_game;

    class AM* am;
    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

#define CUBE_DIMENSIONS 50.0F
    float SIZE_CUBE_PERCENT;
    int SIZE_CUBE;

    bool isPause;
    void show_gui(bool show);


};

