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

    virtual ISTATE* handleInput(const sf::Event&) override;
    virtual void update(const float&) override;
    virtual void render() override;

    virtual void show() override;
    virtual void hide() override;
    virtual void startUp() override;

    void setToPlay();

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

    void (GAME::* curr_ren_fun)()const;
    void (GAME::* curr_upd_fun)(const float& tt);
    ISTATE* (GAME::* curr_hdl_fun)(const sf::Event& event);

private:
    ISTATE* standard_input(const sf::Event& event);
    ISTATE* pause_input(const sf::Event& event);
    ISTATE* gameover_input(const sf::Event& event);

    void standard_render()const;
    void pause_render()const;
    void gameover_render()const;

    void set_pausemode();
    void set_standardmode();
    void set_gameovermode();

    void show_pause_menu(bool show);
    void show_gameover_menu(bool show);

    void update_hightscore();
    std::string get_date()const;
    virtual void onCreate() override;
};


inline void GAME::set_pausemode()
{
    curr_hdl_fun = &GAME::pause_input;
    curr_ren_fun = &GAME::pause_render;
}
inline void GAME::set_standardmode()
{
    curr_hdl_fun = &GAME::standard_input;
    curr_ren_fun = &GAME::standard_render;
}
inline void GAME::set_gameovermode()
{
    curr_hdl_fun = &GAME::gameover_input;
    curr_ren_fun = &GAME::gameover_render;
}


