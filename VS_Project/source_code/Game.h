#pragma once

#include "STATE.h"
#include "WORLD.h"
#include "Tetromino.h"

namespace gui
{
    class Button;
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

    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

    bool isPause;
    void show_gui(bool show);

    virtual void onCreate() override;
};

