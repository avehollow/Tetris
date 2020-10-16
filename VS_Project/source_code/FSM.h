#pragma once

#include "STATE.h"
class FSM
{
    public:
        FSM(STATE*);
        ~FSM();
        void handleInput(const sf::Event&);
        void update(const float&) const;
        void render() const;

        FSM(const FSM&)  = delete;
        FSM(const FSM&&) = delete;
    private:
        STATE* state_;
};

