#include "pch.h"
#include "FSM.h"

FSM::FSM(STATE* s)
	:  state_(s)
{
}

FSM::~FSM()
{
	delete state_;
}

void FSM::handleInput(const sf::Event& event)
{
	STATE* nstate = state_->handleInput(event);
	if (nstate)
	{
		delete state_;
		state_ = nstate;
	}
}

void FSM::update(const float& dt) const
{
	state_->update(dt);
}

void FSM::render() const
{
	state_->render();
}


