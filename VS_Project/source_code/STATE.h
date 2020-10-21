#pragma once

enum E_STATE
{
    ST_BACK = -2,
    ST_NONE = -1,
    ST_MAINMENU = 0,
    ST_GAME,
    ST_OPTIONS,
};


class STATE
{
    public:
         virtual E_STATE handleInput(const sf::Event&) = 0;
         virtual void update(const float&) = 0;
         virtual void render() const = 0;
         virtual void show() = 0;
         virtual void hide() = 0;

        virtual ~STATE() {};

    protected:
        class GameWindow* window;
        class AM* AM_;
};

