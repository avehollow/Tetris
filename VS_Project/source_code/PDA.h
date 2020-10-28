#pragma once
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


    PDA(const PDA&) = delete;
    PDA(PDA&&) = delete;

    PDA& operator=(const PDA&) = delete;
    PDA& operator=(PDA&&) = delete;

private:
    std::stack<class STATE*> states_;
    std::array<class STATE*, 3> data_states_;
};


