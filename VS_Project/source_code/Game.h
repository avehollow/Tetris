#pragma once

#include "STATE.h"

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

private:
    // GUI
    sf::RectangleShape background_pause;

    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

    void show_gui(bool show);
    bool isPause;

    //
    sf::RectangleShape background_game;
    sf::RectangleShape background_tetromino;
    sf::RectangleShape tetromino[200];
    float SIZE_CUBE_PERCENT;
    float SIZE_CUBE;

#define CUBE_DIMENSIONS 50.0F

    int collisions[200];
};

