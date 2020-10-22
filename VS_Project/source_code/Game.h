#pragma once

#include "STATE.h"
#include "Figure.h"
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

private:
    Tetromino tetromino;
    Figure figure;

    sf::RectangleShape background_pause;
    sf::RectangleShape background_game;

    gui::Button* b_Options;
    gui::Button* b_Back;
    gui::Button* b_Exit;

#define CUBE_DIMENSIONS 50.0F
    float SIZE_CUBE_PERCENT;
    int SIZE_CUBE;

    bool isPause;
    void show_gui(bool show);

    bool check_collision(float dir_x, float dir_y);
    bool collision_with_edges(float dir_x, float dir_y);
    bool collision_with_cubes(float dir_x, float dir_y);
    void rotate();
    bool wall_kick();
};

