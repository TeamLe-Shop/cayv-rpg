#include <memory>

#include "window.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "init.hpp"
#include "log.hpp"
#include "scenes/autismofields.hpp"
#include "format.h"

using namespace cayv;

int main()
{
    if (!init()) {
        return 1;
    }

    // New scope to run shit to make sure the destructors run
    {
        Window w("Bursting bubbles fill the air", 640, 480, false, 320, 240);

        Game g(&w);
        g.AddScene(std::make_unique<AutismoFields>("test", &g));
        g.SetScene("test");
        g.Cycle();
    }

    // This should run last, after everything using SDL has been destroyed.
    cleanup();

    return 0;
}
