#pragma once

#include <stack>
#include "Options.h"
#include "MainMenu.h"
#include "Game.h"


class PDA
{
public:
    PDA(class GameWindow* w, class AM*);
    ~PDA();
    void handleInput(const sf::Event&);
    void update(float) const;
    void render() const;
    inline bool empty()const;


    PDA(const PDA&) = delete;
    PDA(PDA&&) = delete;

    PDA& operator=(const PDA&) = delete;
    PDA& operator=(PDA&&) = delete;

private:
    std::stack<class STATE*> states_;

    MAINMENU main_menu;
    GAME game;
    OPTIONS options;

    STATE* st_ptrs[3] = { &main_menu, &game, &options};
};

inline bool PDA::empty()const
{
    return states_.empty();
}

