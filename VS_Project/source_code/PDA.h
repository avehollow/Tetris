#pragma once

template<typename T>
class PDA
{
public:
    PDA(T* state);
    ~PDA();
    void handleInput(const sf::Event&);
    void update(float tt) const;
    void render() const;


    PDA(const PDA&) = delete;
    PDA(PDA&&) = delete;

    PDA& operator=(const PDA&) = delete;
    PDA& operator=(PDA&&) = delete;

private:
    std::stack<T*> states_;
};

template<typename T>
PDA<T>::PDA(T* state)
{
	states_.push(state);
}

template<typename T>
PDA<T>::~PDA()
{

}

template<typename T>
inline void PDA<T>::handleInput(const sf::Event& event)
{
	T* nstate = states_.top()->handleInput(event);
	if (nstate == states_.top())
	{
		return;
		// do nothing
	}
	else if (nstate == nullptr)
	{
		states_.top()->hide();
		states_.pop();
		states_.top()->show();

	}
	else
	{
		states_.top()->hide();
		states_.push(nstate);
		states_.top()->show();
	}
}

template<typename T>
inline void PDA<T>::update(float tt) const
{
	states_.top()->update(tt);
}

template<typename T>
inline void PDA<T>::render() const
{
	states_.top()->render();
}

