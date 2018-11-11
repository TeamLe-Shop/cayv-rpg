#include <memory>

#include "window.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "init.hpp"
#include "log.hpp"
#include "scenes/autismofields.hpp"
#include "scenes/tilesandbox.hpp"
#include "format.h"
#include "resource.hpp"

using namespace cayv;

int main(int argc, char ** argv)
{
    bool tilesandbox = false;
    if (argc > 1 && strcmp(argv[1], "-ts") == 0) {
        tilesandbox = true;
    }
    if (!init()) {
        return 1;
    }

    resource::Bundle b("base", "testbundle.tar", resource::BASE);

    // New scope to run shit to make sure the destructors run
    {
        Window w("Bursting bubbles fill the air", 640, 480, false, 320, 240);

        Game g(&w);
        if (!tilesandbox) {
            g.AddScene(std::make_unique<AutismoFields>("test", &g));
            g.SetScene("test");
        } else {
            g.AddScene(std::make_unique<TileSandbox>("tilesandbox", &g));
            g.SetScene("tilesandbox");
        }
        g.Cycle();
    }

    // This should run last, after everything using SDL has been destroyed.
    cleanup();

    return 0;
}
