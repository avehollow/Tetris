#include "pch.h"
#include "STATE.h"
#include "PDA.h"


PDA::PDA()
{
	
}

PDA::~PDA()
{
	
}

void PDA::handleInput(const sf::Event& event)
{
	if (states_.empty())
		return;

	STATE* nstate = states_.top()->handleInput(event);
	if (nstate == states_.top())
	{
		// do nothing
	}
	else if (nstate == nullptr)
	{
		states_.top()->hide();
		states_.pop();

		if (!states_.empty())
			states_.top()->show();
	}
	else
	{
		states_.top()->hide();
		states_.push(nstate);
		states_.top()->show();
	}
}

void PDA::update(float dt) const
{
	if(!states_.empty())
		states_.top()->update(dt);
}

void PDA::render() const
{
	if(!states_.empty())
		states_.top()->render();
}

void PDA::add(STATE* s)
{
	states_.push(s);
	s->show();
}
