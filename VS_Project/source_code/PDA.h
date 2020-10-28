#pragma once


class PDA
{
public:
    PDA(class STATE* state);
    ~PDA();
    void handleInput(const sf::Event&);
    void update(float tt) const;
    void render() const;


    PDA(const PDA&) = delete;
    PDA(PDA&&) = delete;

    PDA& operator=(const PDA&) = delete;
    PDA& operator=(PDA&&) = delete;

private:
    std::stack<class STATE*> states_;
};


