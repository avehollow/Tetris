#pragma once
#include "GameWindow.h"
#include "assetmanager.h"

#define FS

class WORLD
{
    friend class System;
protected:
    static class GameWindow* window;
    static class AM_* AM;

private:
   static void ini();
   static void free();
};

