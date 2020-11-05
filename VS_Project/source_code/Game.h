#pragma once

#include "STATE.h"
#include "WORLD.h"
#include "Tetromino.h"

namespace gui
{
    class Button;
    class TextBox;
};

class GAME: public ISTATE, public WORLD
{
public:
    GAME() = default;
    virtual ~GAME() = default;
    void setToPlay();


    virtual ISTATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() const override;


    virtual void show() override;
    virtual void hide() override;
    virtual void startUp() override;

private:
    Tetromino tetromino;

    sf::RectangleShape background_pause;
    sf::RectangleShape background_game;
    sf::RectangleShape background_gameover;

    // Pause menu
    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

    // GameOver menu
    gui::TextBox* txb_Nick;
    gui::Button* b_PlayAgain;
    gui::Button* b_Exit2;
    sf::Text txGameOver;
    sf::Text txScore;
    sf::Text txDate;

    bool bPause;
    bool bGameOver;
    int score;
    void show_gui(bool show);

    virtual void onCreate() override;
};

