#include "SDL.h"

#include "window.hpp"

using namespace cayv;

int main()
{
    Window w = Window("44 Flies On Leashes", 2, -1, false);
    w.DrawLoop();
    return 0;
}
