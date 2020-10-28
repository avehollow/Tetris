#pragma once


class WORLD
{
    friend class System;
private:
   static void ini();
   static void free();
protected:
    static class GameWindow* window;
    static class AM_* AM;
};

