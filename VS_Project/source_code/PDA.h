#pragma once

#include <stack>

class PDA
{
public:
    PDA();
    ~PDA();
    void handleInput(const sf::Event&);
    void update(float) const;
    void render() const;
    void add(STATE*);
    inline bool empty()const;
    
private:
    std::stack<class STATE*> states_;
};

inline bool PDA::empty()const
{
    return states_.empty();
}

