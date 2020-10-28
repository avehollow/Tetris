#pragma once
#include "WORLD.h"

class STATE : public WORLD
{
    public:
         virtual STATE* handleInput(const sf::Event&) = 0;
         virtual void update(const float&) = 0;
         virtual void render() const = 0;
         virtual void show() = 0;
         virtual void hide() = 0;
         virtual void onCreate() = 0;
         virtual void ini() = 0;
         virtual ~STATE() {};
};

