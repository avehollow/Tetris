#include "pch.h"
//#include "PDA.h"
//#include "STATE.h"
//
//PDA::PDA(class STATE* state)
//{
//	states_.push(state);
//}
//
//PDA::~PDA()
//{
//
//}
//
//void PDA::handleInput(const sf::Event& event)
//{
//	
//	STATE* nstate = states_.top()->handleInput(event);
//	if (nstate == states_.top())
//	{
//		return;
//		// do nothing
//	}
//	else if (nstate == nullptr)
//	{
//		states_.top()->hide();
//		states_.pop();
//		states_.top()->show();
//		
//	}
//	else
//	{
//		states_.top()->hide();
//		states_.push(nstate);
//		states_.top()->show();
//	}
//}
//
//void PDA::update(float tt) const
//{
//	states_.top()->update(tt);
//}
//
//void PDA::render() const
//{
//	states_.top()->render();
//}
