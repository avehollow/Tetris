#pragma once

class STATE
{
    public:
         virtual STATE* handleInput(const sf::Event&) = 0;
         virtual void update(const float&) = 0;
         virtual void render() const = 0;

        virtual ~STATE() {};
};

